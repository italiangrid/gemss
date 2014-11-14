#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <dmapi.h>
#include <sys/xattr.h>

int main(int argc, char **argv) {

   dm_sessid_t sid = DM_NO_SESSION;

   void *dmhandle=NULL;

   size_t dmhandle_len=0;

   dm_region_t region = { 0, 0, 0 };

   u_int nelem = 0;

   dm_boolean_t exactflagp;

   dm_attrname_t attrname;

   if(argc<2) {
      fprintf(stderr,"Usage: %s <file name>\n", argv[0]);
      return 1;
   }

   if (dm_create_session(DM_NO_SESSION, "setreg", &sid)!=0) {
      fprintf(stderr,"dm_create_session: failed, %s\n", strerror(errno));
      return 1;
   }

   if (dm_path_to_handle(argv[1], &dmhandle, &dmhandle_len) != 0) {
      fprintf(stderr,"dm_path_to_handle: failed, %s\n", strerror(errno));
      dm_destroy_session(sid);
      return 1;
   }

   if (dm_get_region(sid, dmhandle, dmhandle_len, DM_NO_TOKEN, 1, &region, &nelem)) {
      fprintf(stderr, "dm_get_region failed, %s\n", strerror(errno));
      dm_handle_free(dmhandle, dmhandle_len);
      dm_destroy_session(sid);
      return 1;
   }

   if(region.rg_flags & DM_REGION_READ) {
     fprintf(stderr, "Error. File has READ managed region set. The file must be on disk to invalidate the copy on tape.\n");
     dm_handle_free(dmhandle, dmhandle_len);
     dm_destroy_session(sid);
     return 1;
   }

   if(!(region.rg_flags & (DM_REGION_WRITE|DM_REGION_TRUNCATE))) {
     fprintf(stderr, "Error. File does not WRITE and TRUNCATE managed regions set. The file does not appear to have a copy on tape.\n");
     dm_handle_free(dmhandle, dmhandle_len);
     dm_destroy_session(sid);
     return 1;
   }
 
   region.rg_flags &= ~DM_REGION_WRITE;
   region.rg_flags &= ~DM_REGION_TRUNCATE; 

   if (dm_set_region(sid, dmhandle, dmhandle_len, DM_NO_TOKEN, 1, &region, &exactflagp)) {
     fprintf(stderr, "dm_set_region failed, %s\n", strerror(errno));
     dm_handle_free(dmhandle, dmhandle_len);
     dm_destroy_session(sid);
     return 1;
   }

   memset((void *)&attrname.an_chars[0], 0, DM_ATTR_NAME_SIZE);
   memcpy((void *)&attrname.an_chars[0], "IBMPMig", strlen("IBMPMig"));
   if (dm_remove_dmattr(sid, dmhandle, dmhandle_len, DM_NO_TOKEN, 0, &attrname)) {
      fprintf(stderr,"dm_remove_dmattr: failed, %s\n", strerror(errno));
      dm_handle_free(dmhandle, dmhandle_len);
      dm_destroy_session(sid);
      return 1;
   }


   dm_handle_free(dmhandle, dmhandle_len);
   dm_destroy_session(sid);

   removexattr(argv[1], "user.storm.migrated");
   
   return 0;

}

