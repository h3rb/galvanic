#include "GalvanicHandler.h"

GalvanicHandler galvanicHandler;


int headers_table_do(void* rec, const char* key, const char* value) {
 galvanicHandler.HEADERS.Append(new String(key,value));
 return 1;
}
int get_table_do(void* rec, const char* key, const char* value) {
 galvanicHandler.GET.Append(new String(key,value));
 return 1;
}