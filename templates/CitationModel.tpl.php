<div id="overview">
  <div id="citation">
    <h3>
      <?php print t('Citation:') ?>
      <select name="" class="form-select">
        <option value="0">APA</option>
      </select>
    </h3> 
    <?php print print_r($citation, TRUE); ?>
    <?php print theme_button(array('#value' => 'Add To Bibliography')); ?>
  </div>

  <?php if (isset($abstract)): ?>
    <div id="abstract">
      <h3><?php print t('Abstract:') ?></h3>
      <div id="abstract-content"><?php print print_r($abstract, TRUE); ?></div>
    </div>
  <?php endif; ?>
</div>