<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>colorCoordinate</title>
    <?php echo Asset::js('colorCoordinate.js'); ?>
    <link rel="stylesheet" type="text/css" href="<?php echo Uri::base(false); ?>assets/css/colorCoordinate_print.css" media="print">
    <link rel="shortcut icon" href="./favicon.ico" />
</head>
<body>
    <!-- colors=x, size=n -->
    <?php if(!isset($_GET['size']) || !isset($_GET['rows'])):?>
    
    <?php include "getMode.php"?>

    <?php else: ?>

    <!-- Logo -->
    <main class="noscreen print-main">
        <div class="print-logo">
            <h1>C<span class="noscreen glyphicon glyphicon-tint"></span>G</h1>
            <h3>Color Genius</h3>
        </div>
    </main>

    <?php include "upperTable.php"?>
    <?php include "lowerTable.php"?>
    <!-- BUTTONS -->
    <div class="btn-container">
        <button onclick="window.print();" class="btn btn-default" >Print</button>
        <button value="Start Over" class="btn btn-default"><a href="./colorCoordinate">Start Over</a></button>
    </div>

    <?php endif; ?>
    
</body>
</html>
