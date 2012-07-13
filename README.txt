Initial work on Trip.ee D6 to D7 migration. 

Installation:

```  
cd sites/all/modules
git clone https://github.com/kristjanjansen/trip_migrate
git clone --branch 7.x-2.x http://git.drupal.org/sandbox/mikeryan/1234554.git
drush en trip_migrate -y
```  

Then add following snippet to sites/default/settings.php:

```  
$databases['trip']['default'] = array (
  'driver' => 'mysql',
  'database' => 'your_trip_database_name',
  'username' => 'your_trip_database_username',
  'password' => 'your_trip_database_password',
);
```  