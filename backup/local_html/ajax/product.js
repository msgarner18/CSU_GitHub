$(function() {
    $.ajaxSetup ({
        // Disable caching of AJAX responses */
        cache: false
    });
    let $description = $("#description");
    let $image = $("#image");
    let image_sources = ["img/dominion-base.webp", "img/dominion-dark-ages.jpeg", "img/dominion-hinterlands.jpeg"];
    let descriptions = ["descriptions/base.html", "descriptions/dark-age.html", "descriptions/hinterlands.html"];
    let i = 0;

    $description.load(descriptions[0]);
    $image.attr("src", image_sources[0])
    $(".right-button").click(function(){
        i += 1;
        i = i%3;
        $description.load(descriptions[i]);
        $image.attr("src", image_sources[i])
    })
    $(".left-button").click(function(){
        i += 2;
        i = i%3;
        $description.load(descriptions[i]);
        $image.attr("src", image_sources[i])
    })
})