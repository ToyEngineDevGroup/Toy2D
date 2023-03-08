local PlayerController = {
    name = "PlayerController",
    elapsed_time = 0,
    bias = 18,
    speed = 1.0
}

function PlayerController:onCreate()
    print("player create")
end

function PlayerController:onDestroy()
    print("player destroy")
end

function PlayerController:onUpdate(timestep)
    -- print("PlayerController::onUpdate" .. " " .. timestep)

    -- self:mathTest()

    -- print(self.parent:GetName())

    if Input.isKeyPressed(string.byte('W')) then
        self.bias = 6
        self.parent:GetTransform().translation.y = self.parent:GetTransform().translation.y + self.speed * timestep
    end
    if Input.isKeyPressed(string.byte('S')) then
        self.bias = 18
        self.parent:GetTransform().translation.y = self.parent:GetTransform().translation.y - self.speed * timestep
    end
    if Input.isKeyPressed(string.byte('D')) then
        self.bias = 0
        self.parent:GetTransform().translation.x = self.parent:GetTransform().translation.x + self.speed * timestep
    end
    if Input.isKeyPressed(string.byte('A')) then
        self.bias = 12
        self.parent:GetTransform().translation.x = self.parent:GetTransform().translation.x - self.speed * timestep
    end

    self.elapsed_time = self.elapsed_time + timestep
    if self.elapsed_time > 0.1 then
        self.parent:GetTile().coord_x = ((self.parent:GetTile().coord_x + 1) % 6) + self.bias

        self.elapsed_time = self.elapsed_time - 0.1
    end
end

function PlayerController:mathTest()
    -- local vec1 = Vector2:new(1.0, 2.0)
    -- local vec2 = Vector2:new(2.0, 4.0)
    -- print(Vector2.Distance(vec1, vec2))
    -- print(Vector2.Length(vec1))
    -- print(Vector2.SmoothStep(vec1, vec2, 0.5))
    -- print(Vector2.Dot(vec1, vec2))
    -- Vector2.Normalize(vec1)
    -- print(vec1)

    -- local vec1 = Vector3:new(1.0, 2.0, 0.0)
    -- local vec2 = Vector3:new(2.0, 4.0, 6.0)
    -- print(Vector3.Distance(vec1, vec2))
    -- print(Vector3.Length(vec1))
    -- print(Vector3.SmoothStep(vec1, vec2, 0.5))
    -- print(Vector3.Dot(vec1, vec2))
    -- Vector3.Normalize(vec1)
    -- print(vec1)

    local vec1 = Vector4:new(1.0, 2.0, 0.0, 0.0)
    local vec2 = Vector4:new(2.0, 4.0, 6.0, 1.0)
    print(Vector4.Distance(vec1, vec2))
    print(Vector4.Length(vec1))
    print(Vector4.SmoothStep(vec1, vec2, 0.5))
    print(Vector4.Dot(vec1, vec2))
    Vector4.Normalize(vec1)
    print(vec1)

    -- local mat = Matrix:new(1, 1, 1, 1, 1, 1, 1, 4, 2, 2, 2, 2, 2, 2, 2, 2)
    -- print(Matrix.Determinant(mat))

    local c1 = Color:new(0.5, 0.3, 0.2, 1.0)
    Color.AdjustContrast(c1, 0.5)
    print(c1)
end

return PlayerController
