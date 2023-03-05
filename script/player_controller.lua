local PlayerController = {
    name = "PlayerController"
}

function PlayerController:onCreate()
    print("player create")
end

function PlayerController:onDestroy()
    print("player destroy")
end

function PlayerController:onUpdate(timestep)
    print("PlayerController::onUpdate" .. " " .. timestep)
end

return PlayerController
