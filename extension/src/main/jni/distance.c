#include <sqlite3ext.h>
#include <math.h>
#include <assert.h>
SQLITE_EXTENSION_INIT1

// degrees * pi over 180
#define DEG2RAD(degrees) (degrees * 0.01745329251994329) // degrees * pi over 180

// same to AMapUtils.calculateLineDistance
static int distance(double lat1, double lng1, double lat2, double lng2) {
    double lng1rad = DEG2RAD(lng1);
    double lat1rad = DEG2RAD(lat1);
    double lng2rad = DEG2RAD(lng2);
    double lat2rad = DEG2RAD(lat2);

    double sinLng1Rad = sin(lng1rad);
    double sinLat1Rad = sin(lat1rad);
    double cosLng1Rad = cos(lng1rad);
    double cosLat1Rad = cos(lat1rad);

    double sinLng2Rad = sin(lng2rad);
    double sinLat2Rad = sin(lat2rad);
    double cosLng2Rad = cos(lng2rad);
    double cosLat2Rad = cos(lat2rad);

    double v1 = cosLat1Rad * cosLng1Rad;
    double v2 = cosLat2Rad * cosLng2Rad;
    double v3 = cosLat1Rad * sinLng1Rad;
    double v4 = cosLat2Rad * sinLng2Rad;
    double v =  sqrt((v1 - v2) * (v1 - v2) +
        (v3 - v4) * (v3 - v4) +
        (sinLat1Rad - sinLat2Rad) * (sinLat1Rad - sinLat2Rad)
    );

    return asin(v / 2.0) * 12742001.5798544;
}

static void distanceFunc(sqlite3_context *context, int argc, sqlite3_value **argv) {
	// check that we have four arguments (lat1, lon1, lat2, lon2)
	assert(argc == 4);

	// check that all four arguments are non-null
	if (sqlite3_value_type(argv[0]) == SQLITE_NULL || sqlite3_value_type(argv[1]) == SQLITE_NULL || sqlite3_value_type(argv[2]) == SQLITE_NULL || sqlite3_value_type(argv[3]) == SQLITE_NULL) {
		sqlite3_result_null(context);
		return;
	}

	// get the four argument values
	double lat1 = sqlite3_value_double(argv[0]);
	double lng1 = sqlite3_value_double(argv[1]);
	double lat2 = sqlite3_value_double(argv[2]);
	double lng2 = sqlite3_value_double(argv[3]);
	sqlite3_result_int(context, distance(lat1, lng1, lat2, lng2));
}


#ifdef _WIN32
__declspec(dllexport)
#endif
int sqlite3_distance_init(sqlite3 *db, char **pzErrMsg, const sqlite3_api_routines *pApi){
  int rc = SQLITE_OK;
  SQLITE_EXTENSION_INIT2(pApi);
  (void)pzErrMsg;  /* Unused parameter */
  rc = sqlite3_create_function(db, "distance", 4, SQLITE_UTF8, 0, distanceFunc, 0, 0);
  return rc;
}