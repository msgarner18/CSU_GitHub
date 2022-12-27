<?php
    //set size
    $size = 0;
    if(isset($_GET['size']))
        $size = $_GET['size'];

    $letters = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"];
    $chosen_letters = array_slice($letters, 0, $size);
    
    echo "
        <table class='lower_table'>
            <tbody>
                <tr>
                    <th></th>";
                    foreach($chosen_letters as $letter) {
                        echo "<th class='letter'>$letter</th>";
                    }
                    echo "
                </tr>";
                for($i=1; $i < $size+1; $i++) {
                    echo "<tr>";
                        echo "<th>$i</th>";
                    for($j=0; $j < $size; $j++) {
                        echo "<td></td>";
                    }
                    echo "</tr>";
                }
                echo "
            </tbody>
        </table>
    ";
?>