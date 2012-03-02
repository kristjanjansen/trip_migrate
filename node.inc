<?php

/**
 * Common mappings for the Drupal 6 node migrations.
 */
abstract class ExampleNodeMigration extends DrupalNode6Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);
  }
}


class TripForumNodeMigration extends ExampleNodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);
  }

}
