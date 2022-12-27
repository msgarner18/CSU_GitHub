<?php
    // Set row_num
    $row_num = 0;
    if(isset($_GET['rows'])){
        $row_num = $_GET['rows'];
    }

    $colors = ["red", "orange", "yellow", "green", "blue", "purple", "gray", "brown", "black", "teal"];

    echo "
        <p id='color_select_error'>That color has already been selected!</p>
        <table class='upper_table'>";
            for($i=0; $i < $row_num; $i++) {
                echo "
                    <tr>
                        <td class= 'left_col'>
                            <select class='color_select noprint'>"; 
                                foreach(array_values($colors) as $color_index => $color) {
                                    if($color_index == $i)
                                        echo "<option value=$color selected>$color</option>";
                                    else
                                        echo "<option value=$color>$color</option>";
                                }
                                $checked = $i==0 ? "checked" : "";
                                echo "
                            </select>
                            <input class='noprint' type='radio' $checked>
                            <span class='color_select_span noscreen'></span>
                        </td>
                        
                        <td class = 'right_col'></td>
                    </tr>
                ";
            }
            echo "
        </table>
    ";
?>