module.exports = function() {
    var Letter = (letter, line, column) => {
        this.letter = letter;
        this.line = line;
        this.column = column;
        this.overlap = 0;

        return this;
    };

    this.current_line = 1;
    this.current_column = 1;
    this.letters = [];

    this.Add_Letter = (letter) => {
        this.letters.push(new Letter(letter.toLowerCase(), this.current_line, this.current_column));
        this.Add_Column();
    };

    this.Add_Line = () => {
        this.current_line += 1;
        this.current_column = 1;
    };

    this.Add_Column = () => {
        this.current_column += 1;
    }

    this.Size = () => {
        return this.letters.length();
    }

    return this;
}
