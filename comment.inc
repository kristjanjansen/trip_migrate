<?php

class TripCommentMigration extends DrupalComment6Migration {

  public function __construct(array $arguments) {
    parent::__construct($arguments);
  }

  protected function commentQuery($sourceType) {
    $query = Database::getConnection('default', $this->sourceConnection)
             ->select('comments', 'c')
             ->fields('c', array('cid', 'pid', 'nid', 'uid', 'subject',
               'comment', 'hostname', 'timestamp', 'status', 'thread', 'name',
               'mail', 'homepage', 'format'));
    $query->join('node', 'n', 'c.nid = n.nid');
    $query->condition('n.type', $sourceType);
    $query->orderby('c.timestamp', 'ASC');
    
    return $query;
  }

  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }
  
    $row->format = 'filtered_html';
    
  }
   

}