<?php


class TripUserMigration extends DrupalUser6Migration {

	public function __construct(array $arguments) {
		parent::__construct($arguments);

		$this->addFieldMapping('field_user_image', 'filename');
		$this->addFieldMapping('field_user_image:source_dir')
		  ->defaultValue('http://localhost/sites/trip/files/imagecache/trip_picture_big/pictures');
		$this->addFieldMapping('field_user_image:file_replace')
			->defaultValue(FILE_EXISTS_REPLACE);
			
	}

	public function userQuery() {
  	// Do not attempt to migrate the anonymous or admin user rows.
  	$query = Database::getConnection('default', $this->sourceConnection)
  					 ->select('users', 'u')
  					 ->fields('u')
  					 ->condition('uid', 1, '>');
		$query->orderby('uid', 'ASC');
		return $query;
  }
  
	public function prepareRow($row) {

		if (parent::prepareRow($row) === FALSE) {
			return FALSE;
		}
    
		$row->filename = basename($row->picture);
    	
	}
	
	public function complete($user, stdClass $row) {
  
    $user_styles = array('user_tiny', 'user_small', 'user_medium', 'user_big');
    $styles = image_styles(); 
	  foreach ($styles as $key => $style) {
	    if (in_array($key, $user_styles)) {
        $file = file_load($user->field_user_image[LANGUAGE_NONE][0]['fid']);
	      image_style_create_derivative($styles[$key], $file->uri, image_style_path($key, $file->uri));
	      
	    }
	  } 
  
  }
	
	
}
