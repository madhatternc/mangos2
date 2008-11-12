-- extract code with tolua_hide, and also
function extract_code(fn,s)
	if fn ~= "" then
	  local code = '\n$#include "'..fn..'"\n'
        else
          local code = "\n"
        end
	s= "\n" .. s .. "\n" -- add blank lines as sentinels
	local _,e,c,t = strfind(s, "\n([^\n]-)[Tt][Oo][Ll][Uu][Aa]_([^%s]*)[^\n]*\n")
        --print("Found "..e..":"..c..":"..t..":")
	while e do
		t = strlower(t)
		if t == "begin" then
			_,e,c = strfind(s,"(.-)\n[^\n]*[Tt][Oo][Ll][Uu][Aa]_[Ee][Nn][Dd][^\n]*\n",e)
			if not e then
			 tolua_error("Unbalanced 'tolua_begin' directive in header file")
			end
		end
		c = c.."\n"
                local x = string.find(c, "\n[^\n]*[Tt][Oo][Ll][Uu][Aa]_[hH][iI][Dd][eE][^\n]*\n")
                --print("Found hide"..x)
		c = string.gsub(c, "\n[^\n]*[Tt][Oo][Ll][Uu][Aa]_[hH][iI][Dd][eE][^\n]*\n", "\n");
		c = string.gsub(c, "#define[^%(\n]*%(.-\n", "\n")
		code = code .. c
	 _,e,c,t = strfind(s, "\n([^\n]-)[Tt][Oo][Ll][Uu][Aa]_([^%s]*)[^\n]*\n",e)
	end
	return code
end
