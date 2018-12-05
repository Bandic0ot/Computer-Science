package com.mam558.memento;

public class DocumentMemento {
    private String titleState;
    private String bodyState;

    public DocumentMemento(String t, String b) {
        this.titleState = t;
        this.bodyState = b;
    }

    public String getTitleState() {
        return titleState;
    }

    public String getBodyState() {
        return bodyState;
    }

}
