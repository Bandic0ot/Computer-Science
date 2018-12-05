package com.mam558.memento;

import java.util.Stack;

public class Processor {
    private Stack<DocumentMemento> document = new Stack<>();

    public DocumentMemento recoverDocument() {
        return this.document.pop();
    }

    public void saveDocument(DocumentMemento d) {
        this.document.push(d);
    }
}
