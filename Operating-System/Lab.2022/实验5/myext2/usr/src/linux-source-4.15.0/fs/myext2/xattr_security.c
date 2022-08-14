// SPDX-License-Identifier: GPL-2.0
/*
 * linux/fs/myext2/xattr_security.c
 * Handler for storing security labels as extended attributes.
 */

#include "myext2.h"
#include <linux/security.h>
#include "xattr.h"

static int
myext2_xattr_security_get(const struct xattr_handler *handler,
			struct dentry *unused, struct inode *inode,
			const char *name, void *buffer, size_t size)
{
	return myext2_xattr_get(inode, MYEXT2_XATTR_INDEX_SECURITY, name,
			      buffer, size);
}

static int
myext2_xattr_security_set(const struct xattr_handler *handler,
			struct dentry *unused, struct inode *inode,
			const char *name, const void *value,
			size_t size, int flags)
{
	return myext2_xattr_set(inode, MYEXT2_XATTR_INDEX_SECURITY, name,
			      value, size, flags);
}

static int myext2_initxattrs(struct inode *inode, const struct xattr *xattr_array,
			   void *fs_info)
{
	const struct xattr *xattr;
	int err = 0;

	for (xattr = xattr_array; xattr->name != NULL; xattr++) {
		err = myext2_xattr_set(inode, MYEXT2_XATTR_INDEX_SECURITY,
				     xattr->name, xattr->value,
				     xattr->value_len, 0);
		if (err < 0)
			break;
	}
	return err;
}

int
myext2_init_security(struct inode *inode, struct inode *dir,
		   const struct qstr *qstr)
{
	return security_inode_init_security(inode, dir, qstr,
					    &myext2_initxattrs, NULL);
}

const struct xattr_handler myext2_xattr_security_handler = {
	.prefix	= XATTR_SECURITY_PREFIX,
	.get	= myext2_xattr_security_get,
	.set	= myext2_xattr_security_set,
};
