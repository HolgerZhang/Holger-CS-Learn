/* SPDX-License-Identifier: GPL-2.0 */
/*
  File: linux/myext2_xattr.h

  On-disk format of extended attributes for the myext2 filesystem.

  (C) 2001 Andreas Gruenbacher, <a.gruenbacher@computer.org>
*/

#include <linux/init.h>
#include <linux/xattr.h>

/* Magic value in attribute blocks */
#define MYEXT2_XATTR_MAGIC		0xEA020000

/* Maximum number of references to one attribute block */
#define MYEXT2_XATTR_REFCOUNT_MAX		1024

/* Name indexes */
#define MYEXT2_XATTR_INDEX_USER			1
#define MYEXT2_XATTR_INDEX_POSIX_ACL_ACCESS	2
#define MYEXT2_XATTR_INDEX_POSIX_ACL_DEFAULT	3
#define MYEXT2_XATTR_INDEX_TRUSTED		4
#define	MYEXT2_XATTR_INDEX_LUSTRE			5
#define MYEXT2_XATTR_INDEX_SECURITY	        6

struct myext2_xattr_header {
	__le32	h_magic;	/* magic number for identification */
	__le32	h_refcount;	/* reference count */
	__le32	h_blocks;	/* number of disk blocks used */
	__le32	h_hash;		/* hash value of all attributes */
	__u32	h_reserved[4];	/* zero right now */
};

struct myext2_xattr_entry {
	__u8	e_name_len;	/* length of name */
	__u8	e_name_index;	/* attribute name index */
	__le16	e_value_offs;	/* offset in disk block of value */
	__le32	e_value_block;	/* disk block attribute is stored on (n/i) */
	__le32	e_value_size;	/* size of attribute value */
	__le32	e_hash;		/* hash value of name and value */
	char	e_name[0];	/* attribute name */
};

#define MYEXT2_XATTR_PAD_BITS		2
#define MYEXT2_XATTR_PAD		(1<<MYEXT2_XATTR_PAD_BITS)
#define MYEXT2_XATTR_ROUND		(MYEXT2_XATTR_PAD-1)
#define MYEXT2_XATTR_LEN(name_len) \
	(((name_len) + MYEXT2_XATTR_ROUND + \
	sizeof(struct myext2_xattr_entry)) & ~MYEXT2_XATTR_ROUND)
#define MYEXT2_XATTR_NEXT(entry) \
	( (struct myext2_xattr_entry *)( \
	  (char *)(entry) + MYEXT2_XATTR_LEN((entry)->e_name_len)) )
#define MYEXT2_XATTR_SIZE(size) \
	(((size) + MYEXT2_XATTR_ROUND) & ~MYEXT2_XATTR_ROUND)

struct mb_cache;

# ifdef CONFIG_MYEXT2_FS_XATTR

extern const struct xattr_handler myext2_xattr_user_handler;
extern const struct xattr_handler myext2_xattr_trusted_handler;
extern const struct xattr_handler myext2_xattr_security_handler;

extern ssize_t myext2_listxattr(struct dentry *, char *, size_t);

extern int myext2_xattr_get(struct inode *, int, const char *, void *, size_t);
extern int myext2_xattr_set(struct inode *, int, const char *, const void *, size_t, int);

extern void myext2_xattr_delete_inode(struct inode *);

extern struct mb_cache *myext2_xattr_create_cache(void);
extern void myext2_xattr_destroy_cache(struct mb_cache *cache);

extern const struct xattr_handler *myext2_xattr_handlers[];

# else  /* CONFIG_MYEXT2_FS_XATTR */

static inline int
myext2_xattr_get(struct inode *inode, int name_index,
	       const char *name, void *buffer, size_t size)
{
	return -EOPNOTSUPP;
}

static inline int
myext2_xattr_set(struct inode *inode, int name_index, const char *name,
	       const void *value, size_t size, int flags)
{
	return -EOPNOTSUPP;
}

static inline void
myext2_xattr_delete_inode(struct inode *inode)
{
}

static inline void myext2_xattr_destroy_cache(struct mb_cache *cache)
{
}

#define myext2_xattr_handlers NULL

# endif  /* CONFIG_MYEXT2_FS_XATTR */

#ifdef CONFIG_MYEXT2_FS_SECURITY
extern int myext2_init_security(struct inode *inode, struct inode *dir,
			      const struct qstr *qstr);
#else
static inline int myext2_init_security(struct inode *inode, struct inode *dir,
				     const struct qstr *qstr)
{
	return 0;
}
#endif
