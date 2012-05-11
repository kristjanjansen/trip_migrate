<?php


class TripNodeMigration extends DrupalNode6Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);
    $this->addFieldMapping('nid', 'nid');    
    $this->addFieldMapping('is_new')->defaultValue(TRUE);    
  }

  protected function nodeQuery() {
    $query = Database::getConnection('default', $this->sourceConnection)
             ->select('node', 'n')
             ->fields('n', array('nid', 'vid', 'language', 'title', 'uid',
               'status', 'created', 'changed', 'comment', 'promote', 'moderate',
               'sticky'))
             ->condition('type', $this->sourceType)
             ->orderby('n.created', 'DESC');
    $query->innerJoin('node_revisions', 'nr', 'n.vid=nr.vid');
    $query->fields('nr', array('body', 'teaser', 'format'));
    return $query;
  }

}

class TripNodeImageMigration extends TripNodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);
 
    $this->addFieldMapping('field_image_image', 'image');
		$this->addFieldMapping('field_image_image:source_dir')
  		->defaultValue('http://localhost/sites/trip/files/imagecache/trip_image_big');
		$this->addFieldMapping('field_image_image:file_replace')
		  ->defaultValue(FILE_EXISTS_REPLACE);
 
  }

  public function prepareRow($row) {
	  if (parent::prepareRow($row) === FALSE) {
	    return FALSE;
	  }

	  $row->image = TripNodeImageMigration::getImage($row->nid);
	}

  public function getImage($nid) {
    $query = Database::getConnection('default', $this->sourceConnection)
      ->select('content_field_image', 'cfi')
      ->condition('nid', $nid);
    $query->innerJoin('files', 'f', 'cfi.field_image_fid=f.fid');
    $query->fields('f', array('filepath'));
    $results = $query->execute();
    foreach ($results as $result) {
      $filename = basename($result->filepath);
    }
    return $filename;
  }

}