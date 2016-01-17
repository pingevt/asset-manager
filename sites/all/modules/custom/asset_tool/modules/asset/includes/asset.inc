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
   * Override the save method.
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    if (isset($entity->is_new)) {
      $entity->created = REQUEST_TIME;
    }
    $entity->changed = REQUEST_TIME;
    return parent::save($entity, $transaction);
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
    /*
    $form['pager'] = array('#theme' => 'pager');

    $header = array(
      'lawmakers_id' => array('data' => t('Lawmakers ID'), 'field' => 'lawmakers_id'),
      'username' => array('data' => t('Username'), 'field' => 'username'),
      'operations' => array('data' => t('Operations'), 'field' => 'operations'),
    );

    $options = array();
    $search_term = !empty($_GET['search']) ? $_GET['search'] : NULL;

    $query = new EntityFieldQuery();
    $query
      ->entityCondition('entity_type', 'lawmakers');

    if (!empty($search_term)) {
      $query->propertyCondition('username', '%' . $search_term . '%', 'like');
    }
    // Check for sort order and sort key.
    if (!empty($_GET['sort']) && !empty($_GET['order'])) {
      $sort = strtoupper($_GET['sort']);
      $order = strtolower($_GET['order']);
      $order = str_replace(' ', '_', $order);
      if ($order != 'operations') {
        $query->propertyOrderBy($order, $sort);
      }
    }

    $query->pager(TOTAL_ITEMS_PER_PAGE);

    $result = $query->execute();
    $lawmakers_results = !empty($result['lawmakers']) ? $result['lawmakers'] : array();
    $lawmakers_array = !empty($lawmakers_results) ? lawmakers_load_multiple(array_keys($lawmakers_results)) : array();
    foreach ($lawmakers_array as $lawmakers_id => $lawmakers) {
      $options['lawmakers_id-' . $lawmakers_id] = array(
        'lawmakers_id' => l($lawmakers->lawmakers_id, 'lawmakers/' . $lawmakers->lawmakers_id),
        'username' => l($lawmakers->username, 'lawmakers/' . $lawmakers->lawmakers_id),
        'operations' =>
        l(t('View'), 'lawmakers/' . $lawmakers->lawmakers_id) . ' ' .
        l(t('Edit'), ADMIN_CONTENT_LAWMAKERS_MANAGE_URI . $lawmakers_id, array('query' => array('destination' => ADMIN_CONTENT_LAWMAKERS_URI))) . ' ' .
        l(t('Delete'), ADMIN_CONTENT_LAWMAKERS_MANAGE_URI . $lawmakers_id . '/delete', array('attributes' => array('class' => array('lawmakers-delete-' . $lawmakers->lawmakers_id), ), 'query' => array('destination' => ADMIN_CONTENT_LAWMAKERS_URI))),
      );
    }

    $form['search'] = array(
      '#type' => 'fieldset',
      '#title' => t('Basic Search'),
      '#collapsible' => TRUE,
      '#collapsed' => !empty($search_term) ? FALSE : TRUE,
    );

    $form['search']['search_text'] = array(
      '#type' => 'textfield',
      '#title' => t('Search Term'),
      '#default_value' => !empty($search_term) ? $search_term : '',
    );

    $form['search']['search_submit'] = array(
      '#type' => 'submit',
      '#value' => t('Search'),
    );

    $form['bulk_operations'] = array(
      '#type' => 'fieldset',
      '#title' => t('Bulk Operations'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['bulk_operations']['operations'] = array(
      '#type' => 'select',
      '#options' => array(
        0 => t('Select a bulk operation'),
        'delete' => t('Delete selected lawmakers'),
      ),
    );

    $form['bulk_operations']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
    );

    $form['entities'] = array(
      '#type' => 'tableselect',
      '#header' => $header,
      '#options' => $options,
      '#attributes' => array('class' => array('entity-sort-table')),
      '#empty' => t('There are no lawmakers.'),
    );
    */
    return parent::overviewForm($form, $form_state);
  }

  /**
   * Form Submit method.
   */
  public function overviewFormSubmit($form, &$form_state) {
    return parent::overviewFormSubmit($form, $form_state);
    /*
    $values = $form_state['input'];
    $lawmakers_ids = array();

    if (!empty($values['entities'])) {
      foreach ($values['entities'] as $index => $value) {
        if (!empty($value)) {
          $lawmakers_ids[] = str_replace('lawmakers_id-', '', $value);
        }
      }

      switch ($values['operations']) {
        case 'delete':
          drupal_goto('admin/content/lawmakers/bulk/delete/' . implode('|', $lawmakers_ids));
          break;
      }
    }

    if (!empty($values['search_text'])) {
      drupal_goto('admin/content/lawmakers', array('query' => array('search' => $values['search_text'])));
    }
    */
  }
}