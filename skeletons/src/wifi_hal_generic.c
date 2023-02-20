#include <string.h>
#include <stdlib.h>
#include <setjmp.h>

#include "wifi_hal.h"
#include "wifi_hal_generic.h"


INT wifi_init(void)
{
  /*TODO: Implement Me!*/
  return (INT)0;
}

INT wifi_getHalCapability(wifi_hal_capability_t* cap)
{
    /* To ensure that number of radios not returned as a junk value */
    if(cap != NULL)
        cap->wifi_prop.numRadios = 0;

    return (INT)0;
}
