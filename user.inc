<?php


class TripUserMigration extends DrupalUser6Migration {

	public function __construct(array $arguments) {
		parent::__construct($arguments);

		$this->addFieldMapping('field_user_image', 'filename');
		$this->addFieldMapping('field_user_image:source_dir')
		  ->defaultValue('http://localhost/sites/trip/files/pictures');
		$this->addFieldMapping('field_user_image:file_replace')
			->defaultValue(FILE_EXISTS_REPLACE);
	}

	public function userQuery() {
  	// Do not attempt to migrate the anonymous or admin user rows.
  	$query = Database::getConnection('default', $this->sourceConnection)
  					 ->select('users', 'u')
  					 ->fields('u')
  					 ->condition('uid', 1, '>');
		$query->orderby('uid', 'DESC');
		return $query;
  }
  
	public function prepareRow($row) {
		if (parent::prepareRow($row) === FALSE) {
			return FALSE;
		}

		$row->filename = basename($row->picture);
	
	}
	
	
}
