<?php

class Asset extends Entity {

  public function label() {
    return empty($this->title) ? 'Untitled Asset' : $this->title;
  }

  protected function defaultUri() {
    return array('path' => 'assets/' . $this->identifier());
  }
}

class AssetController extends EntityAPIController {

  /**
   * override create().
   */
  public function create(array $values = array()) {
    $values['reports'] = array();
    return parent::create($values);
  }

  /**
   * override load().
   */
  public function load($ids = array(), $conditions = array()) {
    $entities = parent::load($ids, $conditions);

    // Load reports
    foreach ($entities as &$entity) {
      $entity->reports = array();
    }

    return $entities;
  }

  /**
   * Override the save method.
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
dpm($entity);
    if (isset($entity->is_new)) {
      $entity->created = REQUEST_TIME;

      global $user;
      $entity->uid = $user->uid;
    }

    if (isset($entity->description_field)) {
      $entity->description = $entity->description_field['value'];
      $entity->description_format = $entity->description_field['format'];
    }
dpm($entity);
    $entity->changed = REQUEST_TIME;

    $return = parent::save($entity, $transaction);

    // Save/Update reports
dpm($entity);
    foreach ($entity->reports as $n => $report) {
      // Save report record.
      $report = array('aid' => $entity->aid, 'n' => $n);
dpm($report);
      if ($t = drupal_write_record('asset_report', $report)) {
        drupal_set_message($t . ' report', 'notice');
      }
      else {
        drupal_set_message('Did not save report', 'error');
      }
dpm($t);

      // Save individual conditions.
      $conditions = asset_tool_conditions_load();
      foreach ($conditions as $con_id => $cond) {
        $form['reports'][$n][$con_id] = $cond['controller']::saveReports($entity, $n);
      }
    }

    return $return;
  }
}

/**
 * Custom controller for the administrator UI.
 */
class AssetUIController extends EntityDefaultUIController {

  /**
   * Override the menu hook for default ui controller.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['title'] = t('Asset');
    $items[$this->path]['description'] = t('Manage Assets, including fields.');
    $items[$this->path]['access callback'] = 'asset_access_callback';
    $items[$this->path]['access arguments'] = array('administer asset entities');
    $items[$this->path]['type'] = MENU_LOCAL_TASK;
    return $items;
  }

  /**
   * Admin form for searching and doing bulk operations.
   */
  public function overviewForm($form, &$form_state) {
    return parent::overviewForm($form, $form_state);
  }

  /**
   * Form Submit method.
   */
  public function overviewFormSubmit($form, &$form_state) {
    return parent::overviewFormSubmit($form, $form_state);
  }
}