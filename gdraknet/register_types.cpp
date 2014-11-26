#include "register_types.h"
#include "object_type_db.h"
#include "RakNetExample.h"

void register_gdraknet_types()
{
		ObjectTypeDB::register_type<RakNetExample>();
}

void unregister_gdraknet_types() {
   //nothing to do here
}
