mymap = nil

function testFunc (settlement)
	if(mymap == nil) then
		mymap = MapSys.getInstance():getMap()
	end
	return not mymap:isWaterAt(settlement:getX(), settlement:getY())
end
