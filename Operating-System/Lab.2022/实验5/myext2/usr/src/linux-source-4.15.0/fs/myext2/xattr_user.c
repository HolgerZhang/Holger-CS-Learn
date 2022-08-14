// SPDX-License-Identifier: GPL-2.0
/*
 * linux/fs/myext2/xattr_user.c
 * Handler for extended user attributes.
 *
 * Copyright (C) 2001 by Andreas Gruenbacher, <a.gruenbacher@computer.org>
 */

#include <linux/init.h>
#include <linux/string.h>
#include "myext2.h"
#include "xattr.h"

static bool
myext2_xattr_user_list(struct dentry *dentry)
{
	return test_opt(dentry->d_sb, XATTR_USER);
}

static int
myext2_xattr_user_get(const struct xattr_handler *handler,
		    struct dentry *unused, struct inode *inode,
		    const char *name, void *buffer, size_t size)
{
	if (!test_opt(inode->i_sb, XATTR_USER))
		return -EOPNOTSUPP;
	return myext2_xattr_get(inode, MYEXT2_XATTR_INDEX_USER,
			      name, buffer, size);
}

static int
myext2_xattr_user_set(const struct xattr_handler *handler,
		    struct dentry *unused, struct inode *inode,
		    const char *name, const void *value,
		    size_t size, int flags)
{
	if (!test_opt(inode->i_sb, XATTR_USER))
		return -EOPNOTSUPP;

	return myext2_xattr_set(inode, MYEXT2_XATTR_INDEX_USER,
			      name, value, size, flags);
}

const struct xattr_handler myext2_xattr_user_handler = {
	.prefix	= XATTR_USER_PREFIX,
	.list	= myext2_xattr_user_list,
	.get	= myext2_xattr_user_get,
	.set	= myext2_xattr_user_set,
};
