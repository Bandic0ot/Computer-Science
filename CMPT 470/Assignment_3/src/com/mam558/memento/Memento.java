package com.mam558.memento;

public class Memento {
    public static void main(String[] args) {
        Processor wordProcessor = new Processor();
        Document document = new Document();

        document.setTitle("Title");
        document.setBody("This is some text.\n");
        document.printDocument();

        wordProcessor.saveDocument(document.save());

        document.setTitle("New Title");
        document.setBody("This is new text.\n");
        document.printDocument();

        document.retrieve(wordProcessor.recoverDocument());
        document.printDocument();

    }
}
