// SPDX-License-Identifier: GPL-2.0
/*
 * linux/fs/myext2/xattr_trusted.c
 * Handler for trusted extended attributes.
 *
 * Copyright (C) 2003 by Andreas Gruenbacher, <a.gruenbacher@computer.org>
 */

#include "myext2.h"
#include "xattr.h"

static bool
myext2_xattr_trusted_list(struct dentry *dentry)
{
	return capable(CAP_SYS_ADMIN);
}

static int
myext2_xattr_trusted_get(const struct xattr_handler *handler,
		       struct dentry *unused, struct inode *inode,
		       const char *name, void *buffer, size_t size)
{
	return myext2_xattr_get(inode, MYEXT2_XATTR_INDEX_TRUSTED, name,
			      buffer, size);
}

static int
myext2_xattr_trusted_set(const struct xattr_handler *handler,
		       struct dentry *unused, struct inode *inode,
		       const char *name, const void *value,
		       size_t size, int flags)
{
	return myext2_xattr_set(inode, MYEXT2_XATTR_INDEX_TRUSTED, name,
			      value, size, flags);
}

const struct xattr_handler myext2_xattr_trusted_handler = {
	.prefix	= XATTR_TRUSTED_PREFIX,
	.list	= myext2_xattr_trusted_list,
	.get	= myext2_xattr_trusted_get,
	.set	= myext2_xattr_trusted_set,
};
