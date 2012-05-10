<?php


class TripUserMigration extends DrupalUser6Migration {

	public function __construct(array $arguments) {
		parent::__construct($arguments);

		$this->addFieldMapping('field_user_image', 'filename');
		$this->addFieldMapping('field_user_image:source_dir')
		  ->defaultValue('http://localhost/sites/trip/files/pictures');
	}
	  
	public function prepareRow($row) {
		if (parent::prepareRow($row) === FALSE) {
			return FALSE;
		}

		$row->filename = basename($row->picture);
	
	}
	
	
}
