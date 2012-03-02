<?php


abstract class TripNodeMigration extends DrupalNode6Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);
  }
}


class TripForumNodeMigration extends TripNodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);
  }

}

