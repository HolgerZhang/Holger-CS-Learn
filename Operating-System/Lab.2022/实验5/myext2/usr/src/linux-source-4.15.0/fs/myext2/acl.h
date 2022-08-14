/* SPDX-License-Identifier: GPL-2.0 */
/*
  File: fs/myext2/acl.h

  (C) 2001 Andreas Gruenbacher, <a.gruenbacher@computer.org>
*/

#include <linux/posix_acl_xattr.h>

#define MYEXT2_ACL_VERSION	0x0001

typedef struct {
	__le16		e_tag;
	__le16		e_perm;
	__le32		e_id;
} myext2_acl_entry;

typedef struct {
	__le16		e_tag;
	__le16		e_perm;
} myext2_acl_entry_short;

typedef struct {
	__le32		a_version;
} myext2_acl_header;

static inline size_t myext2_acl_size(int count)
{
	if (count <= 4) {
		return sizeof(myext2_acl_header) +
		       count * sizeof(myext2_acl_entry_short);
	} else {
		return sizeof(myext2_acl_header) +
		       4 * sizeof(myext2_acl_entry_short) +
		       (count - 4) * sizeof(myext2_acl_entry);
	}
}

static inline int myext2_acl_count(size_t size)
{
	ssize_t s;
	size -= sizeof(myext2_acl_header);
	s = size - 4 * sizeof(myext2_acl_entry_short);
	if (s < 0) {
		if (size % sizeof(myext2_acl_entry_short))
			return -1;
		return size / sizeof(myext2_acl_entry_short);
	} else {
		if (s % sizeof(myext2_acl_entry))
			return -1;
		return s / sizeof(myext2_acl_entry) + 4;
	}
}

#ifdef CONFIG_MYEXT2_FS_POSIX_ACL

/* acl.c */
extern struct posix_acl *myext2_get_acl(struct inode *inode, int type);
extern int myext2_set_acl(struct inode *inode, struct posix_acl *acl, int type);
extern int myext2_init_acl (struct inode *, struct inode *);

#else
#include <linux/sched.h>
#define myext2_get_acl	NULL
#define myext2_set_acl	NULL

static inline int myext2_init_acl (struct inode *inode, struct inode *dir)
{
	return 0;
}
#endif

