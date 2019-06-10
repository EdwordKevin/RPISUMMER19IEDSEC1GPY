//add button hover animation
function bt_anim(id, img, hover_img){
    $("#"+id).hover(function(){
        $(this).attr("src",hover_img);
    },function(){
        $(this).attr("src",img);
    })
}