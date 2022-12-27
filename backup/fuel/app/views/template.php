<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title><?php echo $title; ?></title>
    <?php echo Asset::css('template.css'); ?>
    <?php echo Asset::css('bootstrap.css'); ?>
    <?php echo Asset::js('jquery-1.11.0.min.js'); ?>
    <?php echo Asset::js('bootstrap.js'); ?>
</head>
<body>
    <header>
        <nav class="navbar navbar-inverse">
            <div class="container-fluid">
                <div class="navbar-header">
                    <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1" aria-expanded="false">
                        <span class="sr-only">Toggle navigation</span>
                        <span class="icon-bar"></span>
                        <span class="icon-bar"></span>
                        <span class="icon-bar"></span>
                    </button>
                    <a class="navbar-brand" href="./index">Color Genius</a>
                </div>

                <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
                    <ul class="nav navbar-nav">
                        <li><a href="./index">Home</a></li>
                        <li><a href="./colorCoordinate">Color Coordinate</a></li>
                        <li><a href="./about">About Us</a></li>
                    </ul>
                </div>
            </div>
        </nav>
    </header>
    <main>
        <div id="wrapper">
            <?php echo $content; ?>
        </div>
    </main>
    <footer>
        <nav class="navbar navbar-inverse navbar-fixed-bottom">
            <div class="container">
                <p class="navbar-text navbar-right">Emmet Prichard | Mark Garner | 2022</p>
            </div>
        </nav>
    </footer>
</body>
</html>

