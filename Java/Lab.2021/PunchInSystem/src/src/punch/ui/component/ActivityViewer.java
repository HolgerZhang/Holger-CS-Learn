package punch.ui.component;

import punch.activity.BasicActivity;
import punch.ui.controller.ActivityDetailController;
import punch.ui.frame.ActivityDetailFrame;
import punch.ui.frame.BasicTemplate;
import punch.ui.frame.MainFrame;

import javax.swing.*;
import java.awt.*;

public class ActivityViewer extends JPanel {
    MainFrame owner;
    BasicActivity activity;
    String mode;
    JButton moreBtn;

    public ActivityViewer(MainFrame owner, BasicActivity activity, String mode) {
        setLayout(new BorderLayout());
        this.owner = owner;
        this.activity = activity;
        this.mode = mode;
        moreBtn = new JButton("更多");
        moreBtn.addActionListener(e -> new ActivityDetailFrame(new ActivityDetailController(owner.getController(), activity, mode), owner).start());
        Box box = Box.createVerticalBox();
        box.add(Box.createVerticalGlue());
        box.add(Box.createVerticalStrut(10));
        JLabel label = new JLabel(activity.getName().trim());
        label.setFont(BasicTemplate.FONT_NORMAL);
        box.add(label);
        box.add(Box.createVerticalStrut(10));
        box.add(new JLabel(activity.getDescription().trim()));
        box.add(Box.createVerticalStrut(10));
        Box btnGroup = Box.createHorizontalBox();
        btnGroup.add(Box.createHorizontalGlue());
        btnGroup.add(moreBtn);
        btnGroup.add(Box.createHorizontalGlue());
        box.add(btnGroup);
        box.add(Box.createVerticalGlue());
        add(box, BorderLayout.CENTER);
    }
}
