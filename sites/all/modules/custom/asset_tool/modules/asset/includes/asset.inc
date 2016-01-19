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
  /*
  public function create(array $values = array()) {

    $values['type'] = 'asset';

    return parent::create($values);
  }
  */

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
    return parent::overviewForm($form, $form_state);
  }

  /**
   * Form Submit method.
   */
  public function overviewFormSubmit($form, &$form_state) {
    return parent::overviewFormSubmit($form, $form_state);
  }
}