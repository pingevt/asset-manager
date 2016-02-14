<?php

?>
<div id="asset-<?php print $asset->aid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
    <h2<?php print $title_attributes; ?>><a href="<?php print $asset_url; ?>"><?php print $title; ?></a></h2>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <div class=""<?php print $content_attributes; ?>>
    <label>Type:</lable>
    <div><?php print $asset->type; ?></div>
    <label>Description:</lable>
    <div><?php print check_markup($asset->description, $asset->description_format); ?></div>
    <label>Starting Year:</lable>
    <div><?php print $asset->start_period_year; ?></div>
    <label>Starting Period:</lable>
    <div><?php print $asset->start_period; ?></div>
    <?php print render($content); ?>

    <a href="/asset/<?php print $asset->aid; ?>/run-report">Run Reports</a>

    <?php print render($report); ?>
  </div>
</div>
