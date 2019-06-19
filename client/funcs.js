//this file contains basic functions used in index.js
let path=require("path");

function sleep(t){
    return new Promise((resolve)=>{setTimeout(()=>{resolve()},t)})
}

//add button hover animation
function bt_anim(selector, hover_img){
    $(selector).each(function(){
        let img;
        $(this).hover(function(){
            img = $(this).attr("src");
            $(this).attr("src",hover_img);
        },function(){
            $(this).attr("src",img);
        });
    });
}

let selected=null;

//add animation of text
function txt_anim(selector, color){
    $(selector).each(function(){
        let cl;
        $(this).hover(function(){
            if(selected==$(this).attr("id")) return;
            cl = $(this).css("color");
            $(this).css("color",color);
        },function(){
            $(this).css("color",cl);
        });
        $(this).click(function(){
            $(this).css("color",cl);
        })
    });
}

//add click task of left bar
function lb_anim(clslct, color, task){
    $(clslct).each(function(){ 
        $(this).click(function(){ 
            if(selected==$(this).attr("id")) return;
            selected= $(this).attr("id");
            $(clslct).css("background","").css("border-left","").css("margin-left","5px").css("color",);
            $(this).css("background",color).css("border-left","solid 5px rgb(86, 152, 206)").css("margin-left","0px");
            task($(this).attr("id"));
        });
    });
}

function fadeout(jq,time){
    return new Promise((resolve)=>{
        jq.css({opacity: 1}).animate({opacity: 0},time,"swing",function(){
            $(this).css({display:"none"});
            console.log("end");
            resolve();
        });
    });
}

function fadein(jq,time){
    return new Promise((resolve)=>{
        jq.css({opacity: 0}).animate({opacity: 1},time,"swing");
        resolve();
    });
}

let first=true;
function showpage(clselector,idselector){
    if(first){
        first=false;
        fadein($(idselector).css({display:"inline"}),200).then(()=>{
            $(idselector).trigger("pageshown");
            console.log(idselector);
        });
        return;
    }
    let outed=null;
    $(clselector).each(function(){
        if($(this).css("display")!="none") {
            outed=fadeout($(this),200);
            outed.then(()=>{
                let fd = fadein($(idselector).css({display:"inline"}),200);
                fd.then(()=>{
                    $(idselector).trigger("pageshown");
                    console.log(idselector);
                })
            });
        }
    })
    
}

function updatemessage(message){
    $("#sttsbar").text(message);
}

function buildchart(cvsid,jsonpath,ylabel,unit,title,color,background){

    //read json
    var filepath = path.join(__dirname, jsonpath);
    var fileexist=new Promise((resolve)=>{
        fs.exists(filepath, function (exists) {
            resolve(exists);
        });
    })
    fileexist.then((exists)=>{
        if(!exists){
            updatemessage("no food data");
            var dates=[];
            var amount=[];
        }else{
            var jsondata = JSON.parse(fs.readFileSync(filepath));
            var dates=jsondata.map((data)=>data.date);
            var amount=jsondata.map((data)=>data.amount);
        }
        if(dates.length>7){
            dates=dates.slice(dates.length-8,dates.length-1);
            amount=amount.slice(amount.length-8,amount.length-1);
        }
        console.log(dates,amount);
        var ctx = document.getElementById(cvsid).getContext('2d');
        Chart.defaults.global.elements.point.pointStyle="cross";
        Chart.defaults.global.legend.display = false;//hide top menu
        var myChart = new Chart(ctx, {
            type: 'line',
            data: {
                labels: dates,
                datasets: [{
                    data: amount,
                    backgroundColor: background,
            
                    borderColor: color,
                    borderWidth: 1
                }]
            },
            options: {
                title: {
                    display: true,
                    text: title,
                },
                scales: {
                    yAxes: [{
                        ticks: {
                            beginAtZero: true,
                        },
                        gridLines:{
                            display:false
                        },
                        scaleLabel:{
                            display:true,
                            labelString:ylabel
                        }
                    }],
                    xAxes: [{
                        gridLines:{
                            display:false
                        }
                    }],
                },
                tooltips: {
                    callbacks: {
                    label: (item) => item.yLabel+unit,
                    },
                },
            }
        });
    })
}
