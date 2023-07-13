sx=sy=0;
function Sz() {
   if (document.all) {
   sxm=document.body.clientWidth+document.body.scrollLeft-137;
   sym=document.body.clientHeight+document.body.scrollTop-71;
   }

   else { 
      sxm=window.innerWidth+pageXOffset-118;
      sym=window.innerHeight+pageYOffset-51;
        }
   if(sx==0) { cls.left=sx=sxm;cls.top=sy=sym }
   if(sxm!=sx)
   if   (Math.abs(sxm-sx)>1)    cls.left=sx+=(sxm-sx)/5;
   else   cls.left=sx=sxm;
   if   (sym!=sy)
   if   (Math.abs(sym-sy)>1)    cls.top=sy+=(sym-sy)/15;
   else   cls.top=sy=sym;
}
document.write("<div id=cls style=position:absolute;width:88;height:31;z-index:15><A HREF=#top>»Øµ½¶¥¶Ë</a></div>");
var cls=(document.all)?document.all.cls.style:document.cls;
setInterval("Sz()",20)

