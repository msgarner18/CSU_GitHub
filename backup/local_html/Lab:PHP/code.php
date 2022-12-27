<!DOCTYPE html>
<html>
    <head>
        <?php include 'widgets/head.php';?>
        <link rel="stylesheet" href="style.css">
        <title>PHP Example</title>
    </head>
    <body>
		<header>
			<h1>PHP examples</h1>
		</header>
		<div>
		<?php
			$csv = array_map('str_getcsv', file('data.csv'));
			for($i=0; $i < sizeof($csv); $i++) {
				echo $csv[$i][0] . ':';
				echo $csv[$i][1] . '<br>';
			}
		?>
		</div>
        <div id="main" class="container">
            
<!--            Example 1-->
            <div id="hello" class="example">
                <?php
                echo "<h4>Hello There!</h4>";
                $greeting = "How's it going?";
                echo "<p> $greeting </p>";
                ?>
                
            </div>
<!--            Example 2-->
            <div id="timestamp" class="example">
                <?php 
                echo "<u>Current date is: " . date("d - m : Y") . "</u>";
                
                date_default_timezone_set("America/Denver");
                echo "<p>The time this page loaded was: " . date("h:i:s") . "</p>";
                ?>
                
            </div>
<!--            Example 3-->
            <div id="list" class="example">
                <?php
                $fruits = array("Apple", "Grape", "Mango", "Banana", "Strawberry");
                echo "<p><b>Favorite Fruits</b></p>";
                echo "<ul>";
                for($x = 0; $x < sizeof($fruits); $x++) {
                    echo "<li>$fruits[$x]</li>";
                }
                echo "</ul>";
                ?>
            
            </div>
<!--            Example 4-->
            <div id="file" class="example">
                <?php
                $contents = fopen('file1.txt', 'r');
                echo "<p><b>" . fgets($contents) . "</b></p>";
                echo "<p><em>" . fgets($contents) . "</em></p>";
                echo "<p id=''>" . fgets($contents) . "</p>";
                ?>
                
            </div>
<!--            Example 5-->
            <div id="calc" class="example">
                
                <?php
                
                echo fgets($contents) . "Calculator!";
                echo "<h1>$greeting</h1>";
                ?>
                
                <form method="get">
                    <input type="number" class="val" name="val1">
                    <select id="oper" name="oper">
                        <option value="1">+</option>
                        <option value="2">-</option>
                        <option value="3">×</option>
                        <option value="4">÷</option>
                        <option value="5">%</option>
                    </select>
                    <input type="number" class="val" name="val2">
                    <button type="submit" name="btn-calc" id="btn-calc">Calculate</button>
                    <?php include 'widgets/calc.php'?>
                </form>
            </div>
<!--WHEN READY RE-DSPLAY ON STYLE-->
            <div class="example">
                <?php
					
                ?>
            </div>
        </div>
    </body>
</html>