/*
 * Copyright 2017, Intel Corporation
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *
 *     * Neither the name of the copyright holder nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#define _GNU_SOURCE

#include "libpmemfile-core.h"
#include "util.h"

#include <dirent.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

extern void verify_consts(void);

void
verify_consts(void)
{
	COMPILE_ERROR_ON(PMEMFILE_O_RDONLY != O_RDONLY);
	COMPILE_ERROR_ON(PMEMFILE_O_WRONLY != O_WRONLY);
	COMPILE_ERROR_ON(PMEMFILE_O_RDWR != O_RDWR);
	COMPILE_ERROR_ON(PMEMFILE_O_ACCMODE != O_ACCMODE);

	COMPILE_ERROR_ON(PMEMFILE_O_CREAT != O_CREAT);
	COMPILE_ERROR_ON(PMEMFILE_O_EXCL != O_EXCL);
	COMPILE_ERROR_ON(PMEMFILE_O_TRUNC != O_TRUNC);
	COMPILE_ERROR_ON(PMEMFILE_O_APPEND != O_APPEND);
	COMPILE_ERROR_ON(PMEMFILE_O_NONBLOCK != O_NONBLOCK);
	COMPILE_ERROR_ON(PMEMFILE_O_NDELAY != O_NDELAY);
	COMPILE_ERROR_ON(PMEMFILE_O_SYNC != O_SYNC);
	COMPILE_ERROR_ON(PMEMFILE_O_ASYNC != O_ASYNC);

#ifdef O_TMPFILE
	COMPILE_ERROR_ON(PMEMFILE_O_TMPFILE != O_TMPFILE);
#endif
	COMPILE_ERROR_ON(PMEMFILE_O_LARGEFILE != O_LARGEFILE);
	COMPILE_ERROR_ON(PMEMFILE_O_DIRECTORY != O_DIRECTORY);
	COMPILE_ERROR_ON(PMEMFILE_O_NOFOLLOW != O_NOFOLLOW);
	COMPILE_ERROR_ON(PMEMFILE_O_CLOEXEC != O_CLOEXEC);
	COMPILE_ERROR_ON(PMEMFILE_O_DIRECT != O_DIRECT);
	COMPILE_ERROR_ON(PMEMFILE_O_NOATIME != O_NOATIME);
	COMPILE_ERROR_ON(PMEMFILE_O_PATH != O_PATH);
	COMPILE_ERROR_ON(PMEMFILE_O_DSYNC != O_DSYNC);

	COMPILE_ERROR_ON(PMEMFILE_S_IFMT != S_IFMT);
	COMPILE_ERROR_ON(PMEMFILE_S_IFDIR != S_IFDIR);
	COMPILE_ERROR_ON(PMEMFILE_S_IFCHR != S_IFCHR);
	COMPILE_ERROR_ON(PMEMFILE_S_IFBLK != S_IFBLK);
	COMPILE_ERROR_ON(PMEMFILE_S_IFREG != S_IFREG);
	COMPILE_ERROR_ON(PMEMFILE_S_IFIFO != S_IFIFO);
	COMPILE_ERROR_ON(PMEMFILE_S_IFLNK != S_IFLNK);
	COMPILE_ERROR_ON(PMEMFILE_S_IFSOCK != S_IFSOCK);

	COMPILE_ERROR_ON(PMEMFILE_AT_SYMLINK_NOFOLLOW != AT_SYMLINK_NOFOLLOW);
	COMPILE_ERROR_ON(PMEMFILE_AT_REMOVEDIR != AT_REMOVEDIR);
	COMPILE_ERROR_ON(PMEMFILE_AT_SYMLINK_FOLLOW != AT_SYMLINK_FOLLOW);
	COMPILE_ERROR_ON(PMEMFILE_AT_NO_AUTOMOUNT != AT_NO_AUTOMOUNT);
	COMPILE_ERROR_ON(PMEMFILE_AT_EMPTY_PATH != AT_EMPTY_PATH);

	COMPILE_ERROR_ON(PMEMFILE_F_DUPFD != F_DUPFD);
	COMPILE_ERROR_ON(PMEMFILE_F_GETFD != F_GETFD);
	COMPILE_ERROR_ON(PMEMFILE_F_SETFD != F_SETFD);
	COMPILE_ERROR_ON(PMEMFILE_F_GETFL != F_GETFL);
	COMPILE_ERROR_ON(PMEMFILE_F_SETFL != F_SETFL);

	COMPILE_ERROR_ON(PMEMFILE_F_RDLCK != F_RDLCK);
	COMPILE_ERROR_ON(PMEMFILE_F_WRLCK != F_WRLCK);
	COMPILE_ERROR_ON(PMEMFILE_F_UNLCK != F_UNLCK);

	COMPILE_ERROR_ON(PMEMFILE_F_GETLK != F_GETLK);
	COMPILE_ERROR_ON(PMEMFILE_F_SETLK != F_SETLK);
	COMPILE_ERROR_ON(PMEMFILE_F_SETLKW != F_SETLKW);

	COMPILE_ERROR_ON(PMEMFILE_SEEK_SET != SEEK_SET);
	COMPILE_ERROR_ON(PMEMFILE_SEEK_CUR != SEEK_CUR);
	COMPILE_ERROR_ON(PMEMFILE_SEEK_END != SEEK_END);
	COMPILE_ERROR_ON(PMEMFILE_SEEK_DATA != SEEK_DATA);
	COMPILE_ERROR_ON(PMEMFILE_SEEK_HOLE != SEEK_HOLE);

	COMPILE_ERROR_ON(PMEMFILE_DT_UNKNOWN != DT_UNKNOWN);
	COMPILE_ERROR_ON(PMEMFILE_DT_FIFO != DT_FIFO);
	COMPILE_ERROR_ON(PMEMFILE_DT_CHR != DT_CHR);
	COMPILE_ERROR_ON(PMEMFILE_DT_DIR != DT_DIR);
	COMPILE_ERROR_ON(PMEMFILE_DT_BLK != DT_BLK);
	COMPILE_ERROR_ON(PMEMFILE_DT_REG != DT_REG);
	COMPILE_ERROR_ON(PMEMFILE_DT_LNK != DT_LNK);
	COMPILE_ERROR_ON(PMEMFILE_DT_SOCK != DT_SOCK);
	COMPILE_ERROR_ON(PMEMFILE_DT_WHT != DT_WHT);

	COMPILE_ERROR_ON(PMEMFILE_MAP_FAILED != MAP_FAILED);
}
