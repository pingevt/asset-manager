<?php

?>

<div class="bg-white pulldown">
    <div class="content content-boxed overflow-hidden">
        <div class="row">
            <div class="col-sm-10 col-sm-offset-1 col-md-6 col-md-offset-3">
                <div class="push-30-t push-50 animated fadeIn">
                    <?php if ($messages): ?>
                      <div class="content bg-white border-b"><?php print $messages; ?></div>
                    <?php endif; ?>

                    <div class="content">
                      <?php if ($page['highlighted']): ?><div id="highlighted"><?php print render($page['highlighted']); ?></div><?php endif; ?>
                      <a id="main-content"></a>
                      <?php print render($title_prefix); ?>
                      <?php if ($title): ?><h1 class="title" id="page-title"><?php print $title; ?></h1><?php endif; ?>
                      <?php print render($title_suffix); ?>
                      <?php if ($tabs): ?><div class="tabs"><?php print render($tabs); ?></div><?php endif; ?>
                      <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
                      <?php print render($page['content']); ?>
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>
