$(function() {
    // print view
    // add colors to left column
    $(".color_select").each(function() {
        $(this).parent().find(".color_select_span").html($(this).val());
    });
    
    // change colors when they are changed
    $(".color_select").change(function() {
        $(this).parent().find(".color_select_span").html($(this).val());
    });



    // color select validation code
    let pColor;
    let $selects = $(".color_select");
    $selects.on('focus', function () {
        pColor = this.value;
    }).change(function() {
        // check if all colors are unique
        let unique_colors = [];
        let isError = false;
        $selects.each(function() {
            let color = $(this).find('option:selected').val();
            if(unique_colors.includes(color)) {
                isError = true;
            }
            else {
                unique_colors.push(color);
            }
        });

        // What I do on error
        if(isError){
            $("#color_select_error").show();
            $(this).val(pColor);
            setTimeout(function() { $("#color_select_error").hide(); }, 3000); 
        }
        else {
            let color = this.value;
            // change color of coordinates in selected row to selected color pColor.
            $myIndex = $(this).parent().parent().index();
            for (el of coordinate_arrs[$myIndex])
            {
                let letter = el[0];
                let number = parseInt(el[1])+1;
                const alphaIndex = (s) => s.toLowerCase().charCodeAt(0) - 97;
                let $td = $(".lower_table tr:nth-child("+number+") td");
                $td.eq(alphaIndex(letter)).attr("style", 'background-color: '+color);
                
            }
        }
        pColor = this.value;
    });



    // Lower table
    let $lower_table_data = $(".lower_table td");
    let coordinate_arrs = {};//{0: [A1, A2], 3: [A3, B2], ...}
    
    $lower_table_data.on('click', function() {
        // change color of lower_table cell
        let $selected_left_col = $("td.left_col:has(input:checked)");
        let $selected_option = $selected_left_col.find(".color_select").find(":selected");
        let selected_color = $selected_option.val();
        $(this).attr("style", 'background-color: '+selected_color); //+' !important'
        
        let col_index = $(this).index();
        let row_num = $(this).parent().index();
        let col_letter = $(".letter")[col_index-1].innerHTML;
        let coordinate = col_letter+row_num;
        let selected_index = $selected_left_col.parent().index();
        
        // add coordinate to current list
        if(selected_index in coordinate_arrs) {
            if(!(coordinate_arrs[selected_index].includes(coordinate))) {
                coordinate_arrs[selected_index].push(coordinate);
            }
        }
        else
            coordinate_arrs[selected_index] = [coordinate];
        
        // remove coordinate from other lists
        for(let key in coordinate_arrs){
            if(key != selected_index) {
                var index = coordinate_arrs[key].indexOf(coordinate);
                if (index !== -1) {
                    coordinate_arrs[key].splice(index, 1);
                }
            }
        }

        // print coordinates in coordinate_arrs to table
        $('.right_col').each(function() {
            let key = $(this).prev().parent().index();
            if(key in coordinate_arrs) {
                let coordinate_list = coordinate_arrs[key].sort().reduce(function(total, value) {
                    return total + value + ", ";
                }, "");
                $(this).html(coordinate_list);
            }
            else {
                $(this).html("");
            }
        });
    });
});