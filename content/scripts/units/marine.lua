hey = false

function update()
   if not hey then
	  print("Uh, nope. It's just me, a marine.")
	  Map.MakeCut(1,9,2,1)
	  hey = true
   end
end
function attacked(attacker, damage)
   return damage
end

