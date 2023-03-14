Data = {
    New = function()
        return {
            Name = "def",
            Age = 0,
            Hometown = "def",

            print = function(this)
                print(this.Name, this.Age, this.Hometown);
            end
        };
    end
};