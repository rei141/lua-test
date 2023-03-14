windowWidth = 640;
windowHeight = 480;
windowName = "hello";

function calc(val1, val2)
    return val1 + val2, val1 - val2, val1 * val2, val1 / val2;
end

function step()
    coroutine.yield("そこは広場だった。");
    coroutine.yield("小さな滑り台があった。");
    coroutine.yield("昔ここで良く遊んだ事を思い出した。");
end

-- require("class");

-- obj1 = Data.New();
-- -- obj1.Age = 50;
-- obj1:print();

-- require("mylib");

start = 10.0;
goal = 30.0;

function glue_test()
    t = 0.0;
    while t < 1.0 do
        Linear(start, goal, t);
        t = t+0.1;
    end
end

-- FuncC();

    -- Linear(10.0,30)