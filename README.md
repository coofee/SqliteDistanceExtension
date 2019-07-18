support sqlite calculate location distance

* beijing location

```kotlin
val pointBeiJing = LatLng(39.904211, 116.407394)
```

* sort location by distance

```sql
select * from location order by distance(lat, lng, 39.904211, 116.407394) limit 100;
```

* compile

set ndk.dir and sdk.dir in local.properties like below

```property
ndk.dir=/xxxx/sdk/ndk-bundle
sdk.dir=/xxx/sdk
```
