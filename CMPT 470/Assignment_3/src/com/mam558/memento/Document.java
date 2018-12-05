package com.mam558.memento;

public class Document {
    private String title;
    private String body;

    public void setTitle(String title) {
        this.title = title;
    }

    public void setBody(String body) {
        this.body = body;
    }

    public String getTitle() {
        return title;
    }

    public String getBody() {
        return body;
    }

    public DocumentMemento save() {
        return new DocumentMemento(this.title, this.body);
    }

    public void retrieve(DocumentMemento m) {
        this.title = m.getTitleState();
        this.body = m.getBodyState();
    }

    public void printDocument() {
        System.out.println(this.getTitle());
        System.out.println(this.getBody());
    }
}
