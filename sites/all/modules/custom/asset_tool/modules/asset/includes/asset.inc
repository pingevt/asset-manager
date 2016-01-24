<?php

class Asset extends Entity {

  public function label() {
    return empty($this->title) ? 'Untitled Asset' : $this->title;
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

      $q = db_select('asset_report', 'ar');
      $q->fields('ar');
      $q->condition('ar.aid', $entity->aid);
      $q->orderBy('n', 'ASC');
      $results = $q->execute();

      while ($row = $results->fetchAssoc()) {
        $entity->reports[$row['n']] = $row;
      }
    }

    return $entities;
  }

  /**
   * Override the save method.
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    if (isset($entity->is_new)) {
      $entity->created = REQUEST_TIME;

      global $user;
      $entity->uid = $user->uid;
    }

    if (isset($entity->description_field)) {
      $entity->description = $entity->description_field['value'];
      $entity->description_format = $entity->description_field['format'];
    }

    $entity->changed = REQUEST_TIME;

    $return = parent::save($entity, $transaction);

    // Save/Update reports
    foreach ($entity->reports as $n => $r) {
      // Save report record.
      $report = array();
      if (isset($r->arid)) {
        $report['arid'] = $r->arid;
      }
      $report += array(
        'aid' => $entity->aid,
        'n' => $n
      );


      foreach ($r as $mod => $vals) {
        if ($mod != 'arid') {
          foreach ($vals as $field => $val) {
            $report[$mod . '_' . $field] = $val;
          }
        }
      }

      if ($t = drupal_write_record('asset_report', $report)) {
        drupal_set_message($t . ' report', 'notice');
      }
      else {
        drupal_set_message('Did not save report', 'error');
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


  protected function overviewTableRow($conditions, $id, $entity, $additional_cols = array()) {
    $entity_uri = entity_uri($this->entityType, $entity);

    $row[] = array('data' => array(
      '#theme' => 'entity_ui_overview_item',
      '#label' => entity_label($this->entityType, $entity),
      '#name' => !empty($this->entityInfo['exportable']) ? entity_id($this->entityType, $entity) : FALSE,
      '#url' => $entity_uri ? $entity_uri : FALSE,
      '#entity_type' => $this->entityType),
    );

    // Add in any passed additional cols.
    foreach ($additional_cols as $col) {
      $row[] = $col;
    }

    // Add a row for the exportable status.
    if (!empty($this->entityInfo['exportable'])) {
      $row[] = array('data' => array(
        '#theme' => 'entity_status',
        '#status' => $entity->{$this->statusKey},
      ));
    }
    // In case this is a bundle, we add links to the field ui tabs.
    $field_ui = !empty($this->entityInfo['bundle of']) && entity_type_is_fieldable($this->entityInfo['bundle of']) && module_exists('field_ui');
    // For exportable entities we add an export link.
    $exportable = !empty($this->entityInfo['exportable']);
    // If i18n integration is enabled, add a link to the translate tab.
    $i18n = !empty($this->entityInfo['i18n controller class']);

    // Add operations depending on the status.
    if (entity_has_status($this->entityType, $entity, ENTITY_FIXED)) {
      $row[] = array('data' => l(t('clone'), $this->path . '/manage/' . $id . '/clone'), 'colspan' => $this->operationCount());
    }
    else {
      $row[] = l(t('edit'), $this->path . '/manage/' . $id);

      if ($field_ui) {
        $row[] = l(t('manage fields'), $this->path . '/manage/' . $id . '/fields');
        $row[] = l(t('manage display'), $this->path . '/manage/' . $id . '/display');
      }
      if ($i18n) {
        $row[] = l(t('translate'), $this->path . '/manage/' . $id . '/translate');
      }
      if ($exportable) {
        $row[] = l(t('clone'), $this->path . '/manage/' . $id . '/clone');
      }

      if (empty($this->entityInfo['exportable']) || !entity_has_status($this->entityType, $entity, ENTITY_IN_CODE)) {
        $row[] = l(t('delete'), $this->path . '/manage/' . $id . '/delete', array('query' => drupal_get_destination()));
      }
      elseif (entity_has_status($this->entityType, $entity, ENTITY_OVERRIDDEN)) {
        $row[] = l(t('revert'), $this->path . '/manage/' . $id . '/revert', array('query' => drupal_get_destination()));
      }
      else {
        $row[] = '';
      }
    }
    if ($exportable) {
      $row[] = l(t('export'), $this->path . '/manage/' . $id . '/export');
    }
    return $row;
  }
}