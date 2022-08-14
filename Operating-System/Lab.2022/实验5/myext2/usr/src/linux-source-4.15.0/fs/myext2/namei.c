// SPDX-License-Identifier: GPL-2.0
/*
 * linux/fs/myext2/namei.c
 *
 * Rewrite to pagecache. Almost all code had been changed, so blame me
 * if the things go wrong. Please, send bug reports to
 * viro@parcelfarce.linux.theplanet.co.uk
 *
 * Stuff here is basically a glue between the VFS and generic UNIXish
 * filesystem that keeps everything in pagecache. All knowledge of the
 * directory layout is in fs/myext2/dir.c - it turned out to be easily separatable
 * and it's easier to debug that way. In principle we might want to
 * generalize that a bit and turn it into a library. Or not.
 *
 * The only non-static object here is myext2_dir_inode_operations.
 *
 * TODO: get rid of kmap() use, add readahead.
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laboratoire MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  from
 *
 *  linux/fs/minix/namei.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  Big-endian to little-endian byte-swapping/bitmaps by
 *        David S. Miller (davem@caip.rutgers.edu), 1995
 */

#include <linux/pagemap.h>
#include <linux/quotaops.h>
#include "myext2.h"
#include "xattr.h"
#include "acl.h"

static inline int myext2_add_nondir(struct dentry *dentry, struct inode *inode)
{
	int err = myext2_add_link(dentry, inode);
	if (!err) {
		d_instantiate_new(dentry, inode);
		return 0;
	}
	inode_dec_link_count(inode);
	unlock_new_inode(inode);
	iput(inode);
	return err;
}

/*
 * Methods themselves.
 */

static struct dentry *myext2_lookup(struct inode * dir, struct dentry *dentry, unsigned int flags)
{
	struct inode * inode;
	ino_t ino;
	
	if (dentry->d_name.len > MYEXT2_NAME_LEN)
		return ERR_PTR(-ENAMETOOLONG);

	ino = myext2_inode_by_name(dir, &dentry->d_name);
	inode = NULL;
	if (ino) {
		inode = myext2_iget(dir->i_sb, ino);
		if (inode == ERR_PTR(-ESTALE)) {
			myext2_error(dir->i_sb, __func__,
					"deleted inode referenced: %lu",
					(unsigned long) ino);
			return ERR_PTR(-EIO);
		}
	}
	return d_splice_alias(inode, dentry);
}

struct dentry *myext2_get_parent(struct dentry *child)
{
	struct qstr dotdot = QSTR_INIT("..", 2);
	unsigned long ino = myext2_inode_by_name(d_inode(child), &dotdot);
	if (!ino)
		return ERR_PTR(-ENOENT);
	return d_obtain_alias(myext2_iget(child->d_sb, ino));
} 

/*
 * By the time this is called, we already have created
 * the directory cache entry for the new file, but it
 * is so far negative - it has no inode.
 *
 * If the create succeeds, we fill in the inode information
 * with d_instantiate(). 
 */
static int myext2_create (struct inode * dir, struct dentry * dentry, umode_t mode, bool excl)
{
	struct inode *inode;
	int err;

	err = dquot_initialize(dir);
	if (err)
		return err;

	inode = myext2_new_inode(dir, mode, &dentry->d_name);
	if (IS_ERR(inode))
		return PTR_ERR(inode);

	inode->i_op = &myext2_file_inode_operations;
	if (test_opt(inode->i_sb, NOBH)) {
		inode->i_mapping->a_ops = &myext2_nobh_aops;
		inode->i_fop = &myext2_file_operations;
	} else {
		inode->i_mapping->a_ops = &myext2_aops;
		inode->i_fop = &myext2_file_operations;
	}
	mark_inode_dirty(inode);
	return myext2_add_nondir(dentry, inode);
}

static int myext2_tmpfile(struct inode *dir, struct dentry *dentry, umode_t mode)
{
	struct inode *inode = myext2_new_inode(dir, mode, NULL);
	if (IS_ERR(inode))
		return PTR_ERR(inode);

	inode->i_op = &myext2_file_inode_operations;
	if (test_opt(inode->i_sb, NOBH)) {
		inode->i_mapping->a_ops = &myext2_nobh_aops;
		inode->i_fop = &myext2_file_operations;
	} else {
		inode->i_mapping->a_ops = &myext2_aops;
		inode->i_fop = &myext2_file_operations;
	}
	mark_inode_dirty(inode);
	d_tmpfile(dentry, inode);
	unlock_new_inode(inode);
	return 0;
}

static int myext2_mknod (struct inode * dir, struct dentry *dentry, umode_t mode, dev_t rdev)
{
	printk(KERN_ERR "oops, `mknod’ is not supported by myext2!\n"); 
	return -EPERM;

//	struct inode * inode;
//	int err;
//
//	err = dquot_initialize(dir);
//	if (err)
//		return err;
//
//	inode = myext2_new_inode (dir, mode, &dentry->d_name);
//	err = PTR_ERR(inode);
//	if (!IS_ERR(inode)) {
//		init_special_inode(inode, inode->i_mode, rdev);
//#ifdef CONFIG_MYEXT2_FS_XATTR
//		inode->i_op = &myext2_special_inode_operations;
//#endif
//		mark_inode_dirty(inode);
//		err = myext2_add_nondir(dentry, inode);
//	}
//	return err;
}

static int myext2_symlink (struct inode * dir, struct dentry * dentry,
	const char * symname)
{
	struct super_block * sb = dir->i_sb;
	int err = -ENAMETOOLONG;
	unsigned l = strlen(symname)+1;
	struct inode * inode;

	if (l > sb->s_blocksize)
		goto out;

	err = dquot_initialize(dir);
	if (err)
		goto out;

	inode = myext2_new_inode (dir, S_IFLNK | S_IRWXUGO, &dentry->d_name);
	err = PTR_ERR(inode);
	if (IS_ERR(inode))
		goto out;

	if (l > sizeof (MYEXT2_I(inode)->i_data)) {
		/* slow symlink */
		inode->i_op = &myext2_symlink_inode_operations;
		inode_nohighmem(inode);
		if (test_opt(inode->i_sb, NOBH))
			inode->i_mapping->a_ops = &myext2_nobh_aops;
		else
			inode->i_mapping->a_ops = &myext2_aops;
		err = page_symlink(inode, symname, l);
		if (err)
			goto out_fail;
	} else {
		/* fast symlink */
		inode->i_op = &myext2_fast_symlink_inode_operations;
		inode->i_link = (char*)MYEXT2_I(inode)->i_data;
		memcpy(inode->i_link, symname, l);
		inode->i_size = l-1;
	}
	mark_inode_dirty(inode);

	err = myext2_add_nondir(dentry, inode);
out:
	return err;

out_fail:
	inode_dec_link_count(inode);
	unlock_new_inode(inode);
	iput (inode);
	goto out;
}

static int myext2_link (struct dentry * old_dentry, struct inode * dir,
	struct dentry *dentry)
{
	struct inode *inode = d_inode(old_dentry);
	int err;

	err = dquot_initialize(dir);
	if (err)
		return err;

	inode->i_ctime = current_time(inode);
	inode_inc_link_count(inode);
	ihold(inode);

	err = myext2_add_link(dentry, inode);
	if (!err) {
		d_instantiate(dentry, inode);
		return 0;
	}
	inode_dec_link_count(inode);
	iput(inode);
	return err;
}

static int myext2_mkdir(struct inode * dir, struct dentry * dentry, umode_t mode)
{
	struct inode * inode;
	int err;

	err = dquot_initialize(dir);
	if (err)
		return err;

	inode_inc_link_count(dir);

	inode = myext2_new_inode(dir, S_IFDIR | mode, &dentry->d_name);
	err = PTR_ERR(inode);
	if (IS_ERR(inode))
		goto out_dir;

	inode->i_op = &myext2_dir_inode_operations;
	inode->i_fop = &myext2_dir_operations;
	if (test_opt(inode->i_sb, NOBH))
		inode->i_mapping->a_ops = &myext2_nobh_aops;
	else
		inode->i_mapping->a_ops = &myext2_aops;

	inode_inc_link_count(inode);

	err = myext2_make_empty(inode, dir);
	if (err)
		goto out_fail;

	err = myext2_add_link(dentry, inode);
	if (err)
		goto out_fail;

	d_instantiate_new(dentry, inode);
out:
	return err;

out_fail:
	inode_dec_link_count(inode);
	inode_dec_link_count(inode);
	unlock_new_inode(inode);
	iput(inode);
out_dir:
	inode_dec_link_count(dir);
	goto out;
}

static int myext2_unlink(struct inode * dir, struct dentry *dentry)
{
	struct inode * inode = d_inode(dentry);
	struct myext2_dir_entry_2 * de;
	struct page * page;
	int err;

	err = dquot_initialize(dir);
	if (err)
		goto out;

	de = myext2_find_entry (dir, &dentry->d_name, &page);
	if (!de) {
		err = -ENOENT;
		goto out;
	}

	err = myext2_delete_entry (de, page);
	if (err)
		goto out;

	inode->i_ctime = dir->i_ctime;
	inode_dec_link_count(inode);
	err = 0;
out:
	return err;
}

static int myext2_rmdir (struct inode * dir, struct dentry *dentry)
{
	struct inode * inode = d_inode(dentry);
	int err = -ENOTEMPTY;

	if (myext2_empty_dir(inode)) {
		err = myext2_unlink(dir, dentry);
		if (!err) {
			inode->i_size = 0;
			inode_dec_link_count(inode);
			inode_dec_link_count(dir);
		}
	}
	return err;
}

static int myext2_rename (struct inode * old_dir, struct dentry * old_dentry,
			struct inode * new_dir,	struct dentry * new_dentry,
			unsigned int flags)
{
	struct inode * old_inode = d_inode(old_dentry);
	struct inode * new_inode = d_inode(new_dentry);
	struct page * dir_page = NULL;
	struct myext2_dir_entry_2 * dir_de = NULL;
	struct page * old_page;
	struct myext2_dir_entry_2 * old_de;
	int err;

	if (flags & ~RENAME_NOREPLACE)
		return -EINVAL;

	err = dquot_initialize(old_dir);
	if (err)
		goto out;

	err = dquot_initialize(new_dir);
	if (err)
		goto out;

	old_de = myext2_find_entry (old_dir, &old_dentry->d_name, &old_page);
	if (!old_de) {
		err = -ENOENT;
		goto out;
	}

	if (S_ISDIR(old_inode->i_mode)) {
		err = -EIO;
		dir_de = myext2_dotdot(old_inode, &dir_page);
		if (!dir_de)
			goto out_old;
	}

	if (new_inode) {
		struct page *new_page;
		struct myext2_dir_entry_2 *new_de;

		err = -ENOTEMPTY;
		if (dir_de && !myext2_empty_dir (new_inode))
			goto out_dir;

		err = -ENOENT;
		new_de = myext2_find_entry (new_dir, &new_dentry->d_name, &new_page);
		if (!new_de)
			goto out_dir;
		myext2_set_link(new_dir, new_de, new_page, old_inode, 1);
		new_inode->i_ctime = current_time(new_inode);
		if (dir_de)
			drop_nlink(new_inode);
		inode_dec_link_count(new_inode);
	} else {
		err = myext2_add_link(new_dentry, old_inode);
		if (err)
			goto out_dir;
		if (dir_de)
			inode_inc_link_count(new_dir);
	}

	/*
	 * Like most other Unix systems, set the ctime for inodes on a
 	 * rename.
	 */
	old_inode->i_ctime = current_time(old_inode);
	mark_inode_dirty(old_inode);

	myext2_delete_entry (old_de, old_page);

	if (dir_de) {
		if (old_dir != new_dir)
			myext2_set_link(old_inode, dir_de, dir_page, new_dir, 0);
		else {
			kunmap(dir_page);
			put_page(dir_page);
		}
		inode_dec_link_count(old_dir);
	}
	return 0;


out_dir:
	if (dir_de) {
		kunmap(dir_page);
		put_page(dir_page);
	}
out_old:
	kunmap(old_page);
	put_page(old_page);
out:
	return err;
}

const struct inode_operations myext2_dir_inode_operations = {
	.create		= myext2_create,
	.lookup		= myext2_lookup,
	.link		= myext2_link,
	.unlink		= myext2_unlink,
	.symlink	= myext2_symlink,
	.mkdir		= myext2_mkdir,
	.rmdir		= myext2_rmdir,
	.mknod		= myext2_mknod,
	.rename		= myext2_rename,
#ifdef CONFIG_MYEXT2_FS_XATTR
	.listxattr	= myext2_listxattr,
#endif
	.setattr	= myext2_setattr,
	.get_acl	= myext2_get_acl,
	.set_acl	= myext2_set_acl,
	.tmpfile	= myext2_tmpfile,
};

const struct inode_operations myext2_special_inode_operations = {
#ifdef CONFIG_MYEXT2_FS_XATTR
	.listxattr	= myext2_listxattr,
#endif
	.setattr	= myext2_setattr,
	.get_acl	= myext2_get_acl,
	.set_acl	= myext2_set_acl,
};
