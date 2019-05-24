/*
 * 
 * 
 * 
 * 
 * */

#define FUSE_USE_VERSION 30

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <fuse.h>
#include <libgen.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>




int MAX_PATH_LENGTH =  PATH_MAX;  // can be used if you want to use a fixed array for paths
int MAX_CONTENT_LENGTH = 10*1024*1024;  // you can assume this maximum content length

#include <gdbm.h> //

GDBM_FILE dbf ;
char* dbFile = NULL;


typedef struct filecontent {
char type ;
off_t size ;//
uid_t user ;//
gid_t group ;//
mode_t permissions ;//
time_t atime ;//
time_t mtime ;//
time_t ctime ;//
char content [0] ;
} filecontent ;

// struct filecontent *ptr = (struct filecontent *)malloc(sizeof filecontent +  whatever_is_needed);

/** Get file attributes.
 *
 * Similar to stat().  The 'st_dev' and 'st_blksize' fields are
 * ignored.  The 'st_ino' field is ignored except if the 'use_ino'
 * mount option is given.
 */
int hw3_getattr(const char *path, struct stat *statbuf)
{
	datum key = {path, strlen(path)+1};
	datum data = gdbm_fetch (dbf , key) ;

	if(data.dsize > 0)
	{
//		printf("girdiiii\n");

		filecontent *ptr = (filecontent *) malloc (sizeof (filecontent ) + data.dsize) ;	
		ptr=data.dptr;
//			st_blocks
//			st_rdev
//			st_nlink
//			st_ino;
		statbuf->st_size=ptr->size;
		statbuf->st_uid=ptr->user;
		statbuf->st_gid=ptr->group;
	
		if(ptr->type == 'D')
			statbuf->st_mode= S_IFDIR | ((unsigned long) ptr->permissions);
		else if(ptr->type == 'R')
			statbuf->st_mode= S_IFREG | ((unsigned long) ptr->permissions);
		else	
			statbuf->st_mode= S_IFLNK | ((unsigned long) ptr->permissions);

		statbuf->st_atime=ptr->atime;
		statbuf->st_mtime=ptr->mtime;
		statbuf->st_ctime=ptr->ctime;

	}
	else
	{
		return -ENOENT;
	}

	return 0;
}

/** Read the target of a symbolic link
 *
 * The buffer should be filled with a null terminated string.  The
 * buffer size argument includes the space for the terminating
 * null character.  If the linkname is too long to fit in the
 * buffer, it should be truncated.  The return value should be 0
 * for success.
 */

//  hw3_readlink: copy content of the path entry stored on gdbm to link parameter (size is the limit on the length, copy at most size bytes).

//ssize_t readlink(const char *restrict path, char *restrict buf, size_t bufsize);

//The readlink() function shall place the contents of the symbolic link referred to by path in the buffer buf which has size bufsize. If the number of bytes in the symbolic link is less than bufsize, the contents of the remainder of buf are unspecified. If the buf argument is not large enough to contain the link content, the first bufsize bytes shall be placed in buf.


int hw3_readlink(const char *path, char *link, size_t size)
{

	datum key = {path, strlen(path)+1};
	datum data = gdbm_fetch (dbf , key) ;
//	link = malloc((size+1) * sizeof(char)); icinde yer ayiramyoz garbage olup gidyo
	if(data.dsize > 0)
	{
		filecontent *ptr = (filecontent *) malloc (sizeof (filecontent ) + data.dsize) ;	
		ptr=data.dptr;

		size_t i=0;
		for(i=1; i<size; i++)
		{
			if(i == strlen(ptr->content))
				break;
			
			link[i-1]=ptr->content[i];
		}
		link[i-1]='\0';
	}
	else
	{
		return -ENOENT;
	}

    return 0;
}

/** Create a file node
 *
 * There is no create() operation, mknod() will be called for
 * creation of all non-directory, non-symlink nodes.
 */
int hw3_mknod(const char *path, mode_t mode, dev_t dev)
{

	datum k = {path, strlen(path)+1};
	datum d = gdbm_fetch (dbf , k) ;

	if(d.dsize > 0)
	{
		return -EEXIST;
	}
	else
{

	int i;
	int index;
	for(i=strlen(path); i>=0; i--)
	{
		if(path[i] == '/')
		{
			index=i;
			break;
		}
	}
	
	char dir_path[index+1];
	char file_name[(strlen(path)-index+1)];

	for(i=0; i<=index; i++)
	{
		dir_path[i]=path[i];
	}
	dir_path[i]='\0';
	int j=0;

	for(i=index+1; i<strlen(path); i++)
	{		
		file_name[j]=path[i];
		j++;	
	}
	file_name[j]='\0';


	if(strlen(dir_path)>1)
	{
		dir_path[strlen(dir_path)-1]='\0';
	}


	datum dkey = {dir_path, strlen(dir_path)+1};
	datum ddata = gdbm_fetch (dbf , dkey) ;

//	printf("dir_path = :   %s\n", dir_path);
//	printf("file_name = :   %s\n", file_name);

	if(ddata.dsize > 0)
	{

		filecontent *ptrd = (filecontent *) malloc (sizeof (filecontent ) + ddata.dsize) ;
		ptrd=ddata.dptr;

		char new_content[strlen(ptrd->content)  + strlen(file_name) +1 ];

		int ii=0;
		for(ii=0; ii<strlen(ptrd->content) ; ii++)
		{
			new_content[ii]=ptrd->content[ii];	
		}
//	printf("new_content = :   %s\n", new_content);

		new_content[ii]='/';

		int jj=0;
		for(ii=strlen(ptrd->content)+1; ii<(strlen(ptrd->content)  + strlen(file_name))+1 ; ii++)
		{
			new_content[ii]=file_name[jj];		
			jj++;
		}
		new_content[ii]='\0';		

//	printf("new_content = :   %s\n", new_content);

		filecontent *val = (filecontent *) malloc (sizeof (filecontent ) + ddata.dsize + 1) ;
		
		val->type=ptrd->type;
		val->size=ptrd->size;
		val->user=ptrd->user;
		val->group=ptrd->group;
		val->permissions=ptrd->permissions;
		val->atime=ptrd->atime;
		val->mtime=ptrd->mtime;
		val->ctime=ptrd->ctime;
			
		int ij=0;		
		for(ij=0; ij<strlen(new_content); ij++)	
			val->content[ij]=new_content[ij];	
			val->content[ij]='\0';		

//	printf("new_content = :   %s\n", val->content);

		datum value = {val, (sizeof(*val)+1+ strlen(val->content))};

		gdbm_store(dbf, dkey, value, GDBM_REPLACE ) ; //

	}
	else
	{
		return -ENOENT;
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	filecontent *ptr = (filecontent *) malloc (sizeof (filecontent ) + 1 + MAX_CONTENT_LENGTH) ;	

	time_t curtime;
	time(&curtime);
	time_t curtime2;
	time(&curtime2);
	time_t curtime3;
	time(&curtime3);
	
	ptr->type='R';
	ptr->permissions = mode;
	ptr->atime = curtime;
	ptr->mtime  = curtime2;
	ptr->ctime  = curtime3;

	ptr->user=getuid();
	ptr->group=getgid();

	datum key = {path, strlen(path)+1};
	datum value2 = {ptr, (sizeof(*ptr))+1+strlen(ptr->content) };///

	gdbm_store(dbf, key, value2, GDBM_INSERT ) ; //


}
    return 0;
}

/** Create a directory */
int hw3_mkdir(const char *path, mode_t mode)
{

	datum k = {path, strlen(path)+1};
	datum d = gdbm_fetch (dbf , k) ;

	if(d.dsize > 0)
	{
		return -EEXIST;
	}
	else
{
	int i;
	int index;
	for(i=strlen(path); i>=0; i--)
	{
		if(path[i] == '/')
		{
			index=i;
			break;
		}
	}

//	char* dir_path = malloc((sizeof(char))*(index+1) );
//	char* file_name = malloc((sizeof(char))*(strlen(path)-index+1));

	char dir_path[index+1];
	char file_name[(strlen(path)-index+1)];
	
	for(i=0; i<=index; i++)
	{
		dir_path[i]=path[i];
	}
		dir_path[i]='\0';
	int j=0;
	for(i=index+1; i<strlen(path); i++)
	{		
		file_name[j]=path[i];
		j++;	
	}
		file_name[j]='\0';

	if(strlen(dir_path)>1)
	{
		dir_path[strlen(dir_path)-1]='\0';
	}

//	printf("dir_path = :   %s\n", dir_path);
//	printf("file_name = :   %s\n", file_name);

		datum dkey = {dir_path, strlen(dir_path)+1};
		datum ddata = gdbm_fetch (dbf , dkey) ;
		
	if(ddata.dsize > 0)
	{

		filecontent *ptrd = (filecontent *) malloc (sizeof (filecontent ) + ddata.dsize) ;
		ptrd=ddata.dptr;


		char new_content[strlen(ptrd->content)  + strlen(file_name) + 1];

		int ii=0;
		for(ii=0; ii<strlen(ptrd->content) ; ii++)
		{

			new_content[ii]=ptrd->content[ii];
		
		}

//	printf("new_content = :   %s\n", new_content);

		new_content[ii]='/';


		int jj=0;
		for(ii=strlen(ptrd->content)+1; ii<(strlen(ptrd->content)  + strlen(file_name)) +1 ; ii++)
		{
			new_content[ii]=file_name[jj];		
			jj++;
		}
			new_content[ii]='\0';		

//	printf("new_content = :   %s\n", new_content);


		filecontent *val = (filecontent *) malloc (sizeof (filecontent ) + ddata.dsize + 1 ) ;
		
		val->type=ptrd->type;
		val->size=ptrd->size;
		val->user=ptrd->user;
		val->group=ptrd->group;
		val->permissions=ptrd->permissions;
		val->atime=ptrd->atime;
		val->mtime=ptrd->mtime;
		val->ctime=ptrd->ctime;
		
		int ij=0;		
		for(ij=0; ij<strlen(new_content); ij++)	
			val->content[ij]=new_content[ij];	
			val->content[ij]='\0';	


		datum value = {val, (sizeof(*val)+1+ strlen(val->content))};


		gdbm_store(dbf, dkey, value, GDBM_REPLACE ) ; //
	}
	else
	{
		return -ENOENT;
	}
	filecontent *ptr = (filecontent *) malloc (sizeof (filecontent ) + MAX_CONTENT_LENGTH + 1) ;	

	time_t curtime;
	time(&curtime);
	time_t curtime2;
	time(&curtime2);
	time_t curtime3;
	time(&curtime3);

	ptr->type='D';
	ptr->permissions = mode;
	ptr->atime = curtime;
	ptr->mtime  = curtime2;
	ptr->ctime  = curtime3;
	ptr->size = 0;

	ptr->user=getuid();
	ptr->group=getgid();


//ptr->content[4];

	ptr->content[0]='.';
	ptr->content[1]='/';
	ptr->content[2]='.';
	ptr->content[3]='.';
	ptr->content[4]='\0';

	datum key = {path, strlen(path)+1};
	datum value2 = {ptr, ((sizeof(*ptr)) + strlen(ptr->content) +1)  };///

	gdbm_store(dbf, key, value2, GDBM_REPLACE ) ; //
}
	return 0;
}

/** Create a symbolic link */
//hw3_symlink: similar to hw3_mknod but file type is 'L'. note that path, the second parameter is the path you create on gdbm. First parameter is the content of the link.

int hw3_symlink(const char *path, const char *link)
{

	datum k = {link, strlen(link)+1};
	datum d = gdbm_fetch (dbf , k) ;

	if(d.dsize > 0)
	{
		return -EEXIST;
	}
	else
{

	int i;
	int index;
	for(i=strlen(link); i>=0; i--)
	{
		if(link[i] == '/')
		{
			index=i;
			break;
		}
	}
	
	char dir_path[index+1];
	char file_name[(strlen(link)-index+1)];

	for(i=0; i<=index; i++)
	{
		dir_path[i]=link[i];
	}
	dir_path[i]='\0';
	int j=0;

	for(i=index+1; i<strlen(link); i++)
	{		
		file_name[j]=link[i];
		j++;	
	}
	file_name[j]='\0';


	if(strlen(dir_path)>1)
	{
		dir_path[strlen(dir_path)-1]='\0';
	}


	datum dkey = {dir_path, strlen(dir_path)+1};
	datum ddata = gdbm_fetch (dbf , dkey) ;

//	printf("dir_path = :   %s\n", dir_path);
//	printf("file_name = :   %s\n", file_name);

	if(ddata.dsize > 0)
	{

		filecontent *ptrd = (filecontent *) malloc (sizeof (filecontent ) + ddata.dsize) ;
		ptrd=ddata.dptr;

		char new_content[strlen(ptrd->content)  + strlen(file_name) +1 ];

		int ii=0;
		for(ii=0; ii<strlen(ptrd->content) ; ii++)
		{
			new_content[ii]=ptrd->content[ii];	
		}
//	printf("new_content = :   %s\n", new_content);

		new_content[ii]='/';

		int jj=0;
		for(ii=strlen(ptrd->content)+1; ii<(strlen(ptrd->content)  + strlen(file_name))+1 ; ii++)
		{
			new_content[ii]=file_name[jj];		
			jj++;
		}
		new_content[ii]='\0';		

//	printf("new_content = :   %s\n", new_content);


		filecontent *val = (filecontent *) malloc (sizeof (filecontent ) + ddata.dsize + 1) ;
		
		val->type=ptrd->type;
		val->size=ptrd->size;
		val->user=ptrd->user;
		val->group=ptrd->group;
		val->permissions=ptrd->permissions;
		val->atime=ptrd->atime;
		val->mtime=ptrd->mtime;
		val->ctime=ptrd->ctime;
			
		int ij=0;		
		for(ij=0; ij<strlen(new_content); ij++)	
			val->content[ij]=new_content[ij];	
			val->content[ij]='\0';		


//	printf("new_content = :   %s\n", val->content);

		datum value = {val, (sizeof(*val)+1+ strlen(val->content))};

		gdbm_store(dbf, dkey, value, GDBM_REPLACE ) ; //

	}
	else
	{
		return -ENOENT;
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	filecontent *ptr = (filecontent *) malloc (sizeof (filecontent ) + 1 + MAX_CONTENT_LENGTH) ;	

	time_t curtime;
	time(&curtime);
	time_t curtime2;
	time(&curtime2);
	time_t curtime3;
	time(&curtime3);
	
	ptr->type='L';
	ptr->permissions = 511;
	ptr->atime = curtime;
	ptr->mtime  = curtime2;
	ptr->ctime  = curtime3;


	ptr->user=getuid();
	ptr->group=getgid();

int c=0;
for(c=0; c<strlen(path); c++)
{
	ptr->content[c]=path[c];/////////////////////////////////////
}

	ptr->content[c]='\0';

	datum key = {link, strlen(link)+1};
	datum value2 = {ptr, (sizeof(*ptr))+1+strlen(ptr->content)};///

	gdbm_store(dbf, key, value2, GDBM_INSERT ) ; //


}


    return 0;
}

/** Change the permission bits of a file */
int hw3_chmod(const char *path, mode_t mode)
{
	datum key = {path, strlen(path)+1};
	datum data = gdbm_fetch (dbf , key) ;
		
	filecontent *ptr = (filecontent *) malloc (sizeof (filecontent ) + data.dsize + + MAX_CONTENT_LENGTH) ;
	ptr=data.dptr;

	ptr->permissions=mode;

	datum value = {ptr, ((sizeof(*ptr)) + strlen(ptr->content) +1)};///

	gdbm_store(dbf, key, value, GDBM_REPLACE ) ; //

	return 0;
}

/** Change the owner and group of a file */
int hw3_chown(const char *path, uid_t uid, gid_t gid)
{
//http://www.thegeekstuff.com/2012/06/chown-examples/

	datum key = {path, strlen(path)+1};
	datum data = gdbm_fetch (dbf , key) ;
		
	filecontent *ptr = (filecontent *) malloc (sizeof (filecontent ) + data.dsize) ;
	ptr=data.dptr;

	ptr->user=uid;
	ptr->group=gid;


	datum value = {ptr, ((sizeof(*ptr)) + strlen(ptr->content) +1)};///
	gdbm_store(dbf, key, value, GDBM_REPLACE ) ; //

    return 0;
}

/** Change the access and/or modification times of a file */
int hw3_utime(const char *path, struct utimbuf *ubuf)
{
// also sets ctime to current time.

	datum key = {path, strlen(path)+1};
	datum data = gdbm_fetch (dbf , key) ;
		
	filecontent *ptr = (filecontent *) malloc (sizeof (filecontent ) + data.dsize) ;
	ptr=data.dptr;

	ptr->atime=ubuf->actime;
	ptr->mtime=ubuf->modtime;

	datum value = {ptr, ((sizeof(*ptr)) + strlen(ptr->content) +1)};///
	gdbm_store(dbf, key, value, GDBM_REPLACE ) ; //

    return 0;
}

/** File open operation
 *
 * No creation, or truncation flags (O_CREAT, O_EXCL, O_TRUNC)
 * will be passed to open().  Open should check if the operation
 * is permitted for the given flags.  Optionally open may also
 * return an arbitrary filehandle in the fuse_file_info structure,
 * which will be passed to all file operations.
 *
 * Changed in version 2.2
 */
int hw3_open(const char *path, struct fuse_file_info *fi)
{
    return 0;
}

/** Read data from an open file
 *
 * Read should return exactly the number of bytes requested except
 * on EOF or error, otherwise the rest of the data will be
 * substituted with zeroes.  An exception to this is when the
 * 'direct_io' mount option is specified, in which case the return
 * value of the read system call will reflect the return value of
 * this operation.
 *
 * Changed in version 2.2
 */
int hw3_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
	datum key = {path, strlen(path)+1};
	datum data = gdbm_fetch (dbf , key) ;

	filecontent *ptr = (filecontent *) malloc (sizeof (filecontent ) + data.dsize + MAX_CONTENT_LENGTH) ;	
	ptr=data.dptr;

	if(data.dsize > 0)
	{
		size_t length=strlen(ptr->content);	
		if(offset >= length)
			return 0;

		if(length < (size+offset))
		{	
			memcpy(buf, ptr->content+offset, length-offset);
			return length-offset;
		}
		else
		{
			memcpy(buf, ptr->content+offset, size);
			return size;
		}				
		
	}
	else
		return -ENOENT;	
}

/** Write data to an open file
 *
 * Write should return exactly the number of bytes requested
 * except on error.  An exception to this is when the 'direct_io'
 * mount option is specified (see read operation).
 *
 * Changed in version 2.2
 */
//hw3_write: get the path entry from gdbm. Modify its size bytes starting at offset and store it back. Note that The size can increase as a result of this operation.

int hw3_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{ //arasira segment alyom

	datum key = {path, strlen(path)+1};
	datum data = gdbm_fetch (dbf , key) ;

	filecontent *ptr = (filecontent *) malloc (sizeof (filecontent ) + data.dsize ) ;	
	ptr=data.dptr;

	if(data.dsize > 0)
	{

		char new_content[strlen(ptr->content) + size + 2];
		int i=0;


		for(i=0; i<(strlen(ptr->content)); i++)
		{
			if(i == (offset))			
				break;
			new_content[i]=ptr->content[i];
		}

		int j=0;
		for(i=offset; i<(size+offset); i++)
		{
			new_content[i]=buf[j];
			j++;		
		}
		for(i=(size+offset); i<(strlen(ptr->content)); i++)
			new_content[i]=ptr->content[i];



/*
		for(i=0; i<strlen(ptr->content); i++)
		{
			new_content[i]=ptr->content[i];
		}
		int j=0;
		for(j=offset; j<strlen(buf); j++)
		{
			if(i==MAX_CONTENT_LENGTH)
				break;
			if(j < (offset+size))
			{
				new_content[i]=buf[j];
				i++;	
			}							
		}
*/
		new_content[i]='\0';
		printf("%s\n",new_content);
		int ij=0;		
		for(ij=0; ij<strlen(new_content); ij++)	
			ptr->content[ij]=new_content[ij];	
			ptr->content[ij]='\0';
		printf("%s\n",ptr->content);

		datum value = {ptr, (sizeof(*ptr)+1+ strlen(ptr->content))};

		gdbm_store(dbf, key, value, GDBM_REPLACE ) ; //
		
	}
	else
		return -ENOENT;

}

/** Release an open file
 *
 * Release is called when there are no more references to an open
 * file: all file descriptors are closed and all memory mappings
 * are unmapped.
 *
 * For every open() call there will be exactly one release() call
 * with the same flags and file descriptor.  It is possible to
 * have a file opened more than once, in which case only the last
 * release will mean, that no more reads/writes will happen on the
 * file.  The return value of release is ignored.
 *
 * Changed in version 2.2
 */
int hw3_release(const char *path, struct fuse_file_info *fi)
{
    return 0;
}

/** Open directory
 *
 * This method should check if the open operation is permitted for
 * this  directory
 *
 * Introduced in version 2.3
 */
int hw3_opendir(const char *path, struct fuse_file_info *fi)
{

	datum key = {path, strlen(path)+1};
	datum data = gdbm_fetch (dbf , key) ;

	if(data.dsize > 0)
	{

	}
	else
		return -ENOENT;	



    return 0;
}

/** Read directory
 *
 * This supersedes the old getdir() interface.  New applications
 * should use this.
 *
 * The filesystem may choose between two modes of operation:
 *
 * 1) The readdir implementation ignores the offset parameter, and
 * passes zero to the filler function's offset.  The filler
 * function will not return '1' (unless an error happens), so the
 * whole directory is read in a single readdir operation.  This
 * works just like the old getdir() method.
 *
 * 2) The readdir implementation keeps track of the offsets of the
 * directory entries.  It uses the offset parameter and always
 * passes non-zero offset to the filler function.  When the buffer
 * is full (or an error happens) the filler function will return
 * '1'.
 *
 * Introduced in version 2.3
 */
int hw3_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi)
{
	datum key = {path, strlen(path)+1};
	datum data = gdbm_fetch (dbf , key) ;

	if(data.dsize > 0)
	{
		filecontent *ptr =(filecontent *) malloc (sizeof (filecontent ) + data.dsize + MAX_CONTENT_LENGTH) ;	
		ptr=(filecontent *) data.dptr;
	
		if(ptr->type == 'D' )
		{
			char * ret;
	  		ret = strtok (ptr->content,"/");
  			while (ret != NULL)
  			{	
				filler(buf, ret, NULL, 0);
    				printf ("%s\n",ret);
   				ret = strtok (NULL, "/");
				
  			}
		}	
	}
	else
		return -ENOENT;	

    return 0;
}

/** Release directory
 *
 * Introduced in version 2.3
 */
int hw3_releasedir(const char *path, struct fuse_file_info *fi)
{
    return 0;
}

/**
 * Initialize filesystem
 *
 * The return value will passed in the private_data field of
 * fuse_context to all file operations and as a parameter to the
 * destroy() method.
 *
 * Introduced in version 2.3
 * Changed in version 2.6
 */
void* hw3_init(struct fuse_conn_info *conn)
{
	
	dbf = gdbm_open ( dbFile, 4096, GDBM_WRCREAT, 0666, 0);
	
	const char *path="/";
	datum key = {path, strlen(path)+1};
	datum data = gdbm_fetch (dbf , key) ;

	if(data.dsize <= 0)
	{
		filecontent *ptr = (filecontent *) malloc (sizeof (filecontent ) + MAX_CONTENT_LENGTH + 1) ;	

		time_t curtime;
		time(&curtime);
		time_t curtime2;
		time(&curtime2);
		time_t curtime3;
		time(&curtime3);

		ptr->type='D';
		ptr->permissions = 384;//////////////////////////////
		ptr->atime = curtime;
		ptr->mtime  = curtime2;
		ptr->ctime  = curtime3;
		ptr->size = 0;

		ptr->user=0;/////////////////////////////////
		ptr->group=0;//////////////////////////////


//ptr->content[4];

		ptr->content[0]='.';
		ptr->content[1]='/';
		ptr->content[2]='.';
		ptr->content[3]='.';
		ptr->content[4]='\0';

		datum key = {path, strlen(path)+1};
		datum value2 = {ptr, ((sizeof(*ptr)) + strlen(ptr->content) +1)  };///

		gdbm_store(dbf, key, value2, GDBM_INSERT ) ;
	}


	return NULL;
}

/**
 * Clean up filesystem
 *
 * Called on filesystem exit.
 *
 * Introduced in version 2.3
 */
void hw3_destroy(void *userdata)
{
		
	gdbm_close (dbf);    
}

/**
 * Check file access permissions
 *
 * This will be called for the access() system call.  If the
 * 'default_permissions' mount option is given, this method is not
 * called.
 *
 * This method is not called under Linux kernel versions 2.4.x
 *
 * Introduced in version 2.5
 */


//int access(const char *pathname, int mode);

//access() checks whether the calling process can access the file pathname. If pathname is a symbolic link, it is dereferenced.
//The mode specifies the accessibility check(s) to be performed, and is either the value F_OK, or a mask consisting of the bitwise OR of one or more of R_OK, W_OK, and X_OK. F_OK tests for the existence of the file. R_OK, W_OK, and X_OK test whether the file exists and grants read, write, and execute permissions, respectively.

//The check is done using the calling process's real UID and GID, rather than the effective IDs as is done when actually attempting an operation (e.g., open(2)) on the file. This allows set-user-ID programs to easily determine the invoking user's authority.

//If the calling process is privileged (i.e., its real UID is zero), then an X_OK check is successful for a regular file if execute permission is enabled for any of the file owner, group, or other.
//Return Value
//On success (all requested permissions granted), zero is returned. On error (at least one bit in mode asked for a permission that is denied, or some other error occurred), -1 is returned, and errno is set a




int hw3_access(const char *path, int mask)
{
/*
		datum key = {path, strlen(path)+1};
		datum data = gdbm_fetch (dbf , key) ;

		filecontent *ptr = (filecontent *) malloc (sizeof (filecontent ) + data.dsize) ;	
		ptr=data.dptr;


		if(data.dsize > 0)
		{

			if(mask == F_OK) 
			{
				return 0;
			}
			if(mask|R_OK)
			{
				if(getuid() == 0) // rootmu
				{
					if((292 & ptr->permissions) > 0) //444=100 100 100
					{
						return 0;
					}
					else
					{
						return -1;
					}	
				}
				else if(ptr->user == getuid())
				{
					if((4 & ptr->permissions) > 0) //004=000 000 100
					{
						return 0;
					}
					else
					{
						return -1;
					}	
				}
				else if(ptr->group  ==  getgid())
				{
					if((32 & ptr->permissions) > 0) //040=000 100 000
					{
						return 0;
					}
					else
					{
						return -1;
					}	

				}
				else
				{
					return -1;	
				}
			}
			if(mask | W_OK)
			{
				if(getuid() == 0) // rootmu
				{
					if((146 & ptr->permissions) > 0) //222=010 010 010
					{
						return 0;
					}
					else
					{
						return -1;
					}						
				}
				else if(ptr->user == getuid())
				{
					if((2 & ptr->permissions) > 0) //002=000 000 010
					{
						return 0;
					}
					else
					{
						return -1;
					}
				}
				else if(ptr->group  ==  getgid())
				{
					if((16 & ptr->permissions) > 0) //020=000 010 000
					{
						return 0;
					}
					else
					{
						return -1;
					}
				}
				else
				{
					return -1;	
				}
			}
			if(mask | X_OK)
			{
				if(getuid() == 0) // rootmu
				{
					if((73 & ptr->permissions) > 0) //111=001 001 001
					{
						return 0;
					}
					else
					{
						return -1;
					}
				}
				else if(ptr->user == getuid())
				{
					if((1 & ptr->permissions) > 0) //001=000 000 001
					{
						return 0;
					}
					else
					{
						return -1;
					}

				}
				else if(ptr->group  ==  getgid())
				{
					if((8 & ptr->permissions) > 0) //010=000 001 000
					{
						return 0;
					}
					else
					{
						return -1;
					}
				}
				else
				{
					return -1;	
				}
			}
			else
				return 0;		
		}
		else
			return -ENOENT;	

*/


    return 0;
}

struct fuse_operations hw3_oper = {
  .getattr = hw3_getattr, //done
  .readlink = hw3_readlink, //done
  .mknod = hw3_mknod, //done
  .mkdir = hw3_mkdir, //done
  .symlink = hw3_symlink, //done
  .chmod = hw3_chmod, //done
  .chown = hw3_chown, //done
  .utime = hw3_utime, //done
  .open = hw3_open,
  .read = hw3_read,	//done
  .write = hw3_write, //almost done
  .release = hw3_release,
  .opendir = hw3_opendir,
  .readdir = hw3_readdir, //done
  .releasedir = hw3_releasedir,
  .init = hw3_init,  //almost done
  .destroy = hw3_destroy,	//almost done
  .access = hw3_access,
};

void hw3_usage()
{
    fprintf(stderr, "usage:  hw3 [FUSE and mount options] gdbmFile mountPoint\n");
    abort();
}

int main(int argc, char *argv[])
{
    int fuse_stat;
    
    dbFile = argv[1];

//////////////////////////////////////////

//dbf = gdbm_open ( dbFile, 4096, GDBM_WRCREAT, 0666, 0);

//	const char *path="/dir1/dir2";

//	const char *link="/linker";

//	hw3_symlink(path, link);

//	mode_t mode=33188;
//	dev_t dev=1;
//	hw3_mknod(path, mode, dev);


//	const char *path="/linker3";
	
//	size_t size = 1;

//	char* link = malloc((size+1) * sizeof(char)); ;
//	hw3_readlink(path, link, size);

//	printf("last =%s\n", link);


//const char *path="/file1";
//const char *buf="/12345/67890/abcde/fghjk/lmnop/qrstuw";

//hw3_write(path, buf, 10, 9, NULL);

//	gdbm_close (dbf);    


////////////////////////////////////////////////////////////////    
    fuse_stat = fuse_main(argc-1, argv+1, &hw3_oper, NULL);
    
    return fuse_stat;

}

