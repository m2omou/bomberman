function IA (player)
   x = math.floor(player:getPos():getX())
   z = math.floor(player:getPos():getZ())
   math.randomseed(os.clock())

   -- If the destination has been reached, then choose a new one
   if player:isDirReached() then
      player:setNewDir()
   end
   -- Apply direction mouvement
   dir = player:getDir()
   if dir == 1 then
      player:moveRight()
   elseif dir == 2 then
      player:moveLeft()
   elseif dir == 3 then
      player:moveDown()
   elseif dir == 4 then
      player:moveUp()
   end
   rd = math.floor(math.random() * 1000) % 2
   if rd == 1 then
      player:plantBomb()
   end
   player:move()
end
