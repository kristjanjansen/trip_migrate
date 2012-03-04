<?php

class TripCommentMigration extends DrupalComment6Migration {

  public function __construct(array $arguments) {
    parent::__construct($arguments);
  }

  protected function commentQuery() {
    $query = Database::getConnection('default', $this->sourceConnection)
      ->select('comments', 'c')
      ->fields('c', array('cid', 'pid', 'nid', 'uid', 'subject',
        'comment', 'hostname', 'timestamp', 'status', 'thread', 'name',
        'mail', 'homepage', 'format'));
    
    $query->innerJoin('node', 'n', 'c.nid=n.nid');
    $query->fields('n', array('type'))
        ->condition('n.type', 'trip_forum')
        ->orderby('c.timestamp', 'DESC');
    
    return $query;
  }

}