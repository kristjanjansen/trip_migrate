<?php


abstract class TripNodeMigration extends DrupalNode6Migration {
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


class TripForumNodeMigration extends TripNodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);
  }

}

