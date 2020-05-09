<!--
// See KB article about changing this dynamic HTML
	function getControlTag(src)
	{
		TRok = false
		while ("HTML" != src.tagName)
		{
			if ("IMG" == src.tagName || "FONT" == src.tagName || "A" == src.tagName || "TD" == src.tagName)
			    TRok = true
			if ("LI" == src.tagName)
				return src
			if ("TR" == src.tagName)
			{
				if(TRok)
					return src
				return null
			}
			src = src.parentElement
		}
		return null
	}
	function dynOutlineEnabled(src)
	{
		while ("BODY" != src.tagName)
		{
			table = "TABLE" == src.tagName;
			if(table && src.getAttribute("border", false) != "0")
				return false;
			if("OL" == src.tagName || "UL" == src.tagName || table)
			{
				if(null != src.getAttribute("nodynamicoutline", false))
					return false
				if(null != src.getAttribute("dynamicoutline", false))
					return true
				if(mac > 0)
				{
					var at = src.outerHTML.indexOf("dynamicoutline")
					if(at > 0)
					{
						var gt = src.outerHTML.indexOf(">")
						if(at < gt)
							return true
					}
				}
			}
			src = src.parentElement
		}
		return false
	}
    function initCollapse(src)
    {
		while ("BODY" != src.tagName)
		{
			table = "TABLE" == src.tagName;
    		if(table && src.getAttribute("border", false) != "0")
    			return false;
        	if("OL" == src.tagName || "UL" == src.tagName || table)
    		{
    			if(null != src.getAttribute("initcollapsed", false))
    				return true
    		}
    		src = src.parentElement
        }
		return false
    }
	function containedIn(src, dest)
	{
		if ("!" == src.tagName)
			return true
		src = getControlTag(src)
		if (src == dest)
		    return true
		return false
	}
    function initOutline()
    {
		var ms = navigator.appVersion.indexOf("MSIE");
    	mac = navigator.appVersion.indexOf("Macintosh");
		ie4 = (ms>0) && (parseInt(navigator.appVersion.substring(ms+5, ms+6)) >= 4);
		if(!ie4)
			return;
        listTags = new Array()
        listTags[0]="UL"
        listTags[1]="OL"
        listTags[2]="TABLE"
        for(j=0;j<listTags.length;j++)
        {
            tagName=listTags[j]
            coll=document.all.tags(tagName)
            for(i=0; i<coll.length; i++)
            {
                if(dynOutlineEnabled(coll[i].parentElement))
                {
                    if(initCollapse(coll[i]))
                        coll[i].style.display="none"
                }
            }
        }        
    }   
	function dynOutline()
	{
		var ms = navigator.appVersion.indexOf("MSIE");
		ie4 = (ms>0) && (parseInt(navigator.appVersion.substring(ms+5, ms+6)) >= 4);
		if(!ie4)
			return;
		var src = event.srcElement
		src = getControlTag(src)
		if (null == src)
			return
		if (!dynOutlineEnabled(src))
			return
		var idx = src.sourceIndex+1
		while (idx < document.all.length && containedIn(document.all[idx], src))
		{
			srcTmp = document.all[idx]
			tag = srcTmp.tagName
			if ("UL" == tag || "OL" == tag || "TABLE" == tag)
				srcTmp.style.display = srcTmp.style.display == "none" ? "" : "none"
			idx++;
		}
	}
//-->
