<!-- To Do:
    What is an intuitive order for the colors?
    Initially, a different color is selected in each dropdown menu
    No two drop downs can select the same color at the same time (if this happens, revert the most recently changed drop down to the previous value that was selected.
    Inform the user of this in a non-intrusive way (i.e. not an alert() ).
-->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title></title>
</head>
<body>
    <!-- colors=x, size=n -->
    <?php if(!isset($_GET['size']) || !isset($_GET['rows'])):?>



    <!-- Any HTML written below here will be displayed when either size or rows is not set -->
    <div class="jumbotron">
        <h1>Start your Color Coordinating Here!</h1>
        
        <div class="jumbo-decoration">
            <p>Fill out this short form declaring how many colors you wish to select from as well as the size of the output table. This will help us better provide a solution for your needs. Choose between up to 10 different color options and display an output table that has a size of anywhere between 1 and 26 rows/columns.</p>
            <br>
            <!-- changed action url and button type -->
            <form action="./colorCoordinate" method="get">
                <label for="rows">Number of colors:</label><br>
                <input type="number" min="1" max="10" id="rows" name="rows" value="1"><br>
                <label for="size">Size of output table:</label><br>
                <input type="number" min="1" max="26" id="size" name="size" value="1"><br><br>
                <input type="submit" id="firstFormButton">
            </form>
        </div>
    </div>
    <!-- Any HTML written above here will be displayed when either size or rows is not set -->

    <!-- <php 
        $rowValid = ($_GET['rows'] <= 10 && $_GET['rows'] >= 1);
        $sizeValid = ($_GET['size'] <= 26 && $_GET['size'] >= 1);
        if(!($rowValid)){
            echo "<script>console.log('Debug Objects: " . $_GET['rows'] . "' );</script>";
            echo "<script>console.log('Debug Objects: HERE" . $rowValid . "' );</script>";
            echo '<script> alert("Invalid row entry. Please enter a number between 1 and 10."); </script>';
        }
        if(!($sizeValid)){
            echo '<script> alert("Invalid size entry. Please enter a number between 1 and 26."); </script>';
        }
        if($sizeValid && $rowValid) $allValid = TRUE;
        else {
            $allValid = FALSE;
            unset($_GET['rows']);
            unset($_GET['size']);
        }
    > -->
    


    <?php else: ?>


    <!-- The rest of the code below will be displayed when both size and colors is set -->
    <h1>Upper Table</h1>
    <?php
        // fills a select tag with options provided in global $colors array
        // returns select tag within <td class='left_col'></td> tag
        // Each time it is called, a unique color is selected as the default color 
        function fill_select($color_index) {
            $select = "<td class= 'left_col'> <select>";
            
            // create options
            $colors = ["red", "orange", "yellow", "green", "blue", "purple", "gray", "brown", "black", "teal"];
            $options = "";
            foreach(array_values($colors) as $i => $color) {
                if($i == $color_index){
                    $options = $options . "<option value={$color} selected>$color</option>";
                }
                else {
                    $options = $options . "<option value={$color}>$color</option>";
                }
            }
            $select = $select . $options;
            $select = $select . "</select> </td>";
            return $select;
            
        }
        // $select is a list of data on left side of table
        // $other is a single data that is repeated on the right side of the table
        function fill_table($select, $other) {
            $table = "<table class='upper_table'>";  
            foreach ($select as $td){
                $table = $table . "<tr>";
                $table = $table . $td . $other;
                $table = $table . "</tr>";
            }
            $table = $table . "</table>";
            return $table;
        }

        // Set row_num
        $row_num = 2;
        if(isset($_GET['rows'])){
            $row_num = $_GET['rows'];
        }
        
        // fill $select with list of unique <td><select></select></td> tags
        $select = [];
        for($i=0; $i < $row_num; $i++){
            $color_list_length = 10;
            $color_index = $i % $color_list_length;
            $select[] = fill_select($color_index);
        }
        $other = "<td class = 'right_col'>Empty Cell</td>";
        $table = fill_table($select, $other);

        // output table
        echo $table;
    ?>

    <h1>Lower Table</h1>
    <?php
        function fill_header($datalist){
            $header = "<th>";
            foreach($datalist as $tabledata){
                $header = $header . "<td>{$tabledata}</td>";
            }
            $header = $header . "</th>";
            return $header;
        }
        function fill_row($tabledata, $size) {
            $row = "<tr>";
            $row = $row . "<td>" . $tabledata . "</td>";
            for($i=0; $i<$size; $i++){
                $row = $row . "<td></td>";
            }
            $row = $row . "</tr>";
            return $row;
        }
        //set size
        $size = 2;
        if(isset($_GET['size']))
            $size = $_GET['size'];

        // header- letters
        $letters = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"];
        $datalist = array_slice($letters, 0, $size);
        $header = fill_header($datalist);

        // Rows- numbers
        $rows = [$header];
        for($i=1; $i <= $size; $i++){
            $rows[] = fill_row($i, $size);
        }
        $table = "<table class='lower_table'>";
        foreach($rows as $row){
            $table = $table . $row;
        }
        $table = $table . "</table>";
        echo $table;
        ?>
    <br>
    <div class="btn-container">
        <button type="submit" class="btn btn-default">Print Results</button>
        <button value="Start Over" class="btn btn-default"><a href="./colorCoordinate">Start Over</a></button>
    </div>
    <?php endif; ?>
    <?php echo Asset::js('colorCoordinate.js'); ?>
</body>
</html>
