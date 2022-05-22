$NetBSD$

Treat NetBSD like Linux.

--- src/slic3r/GUI/UnsavedChangesDialog.cpp.orig	2021-12-17 14:00:02.000000000 +0000
+++ src/slic3r/GUI/UnsavedChangesDialog.cpp
@@ -109,7 +109,7 @@ ModelNode::ModelNode(ModelNode* parent, 
     UpdateIcons();
 }
 
-#ifdef __linux__
+#if defined(__linux__) || defined(__NetBSD__)
 wxIcon ModelNode::get_bitmap(const wxString& color)
 #else
 wxBitmap ModelNode::get_bitmap(const wxString& color)
@@ -127,7 +127,7 @@ wxBitmap ModelNode::get_bitmap(const wxS
     unsigned char rgb[3];
     BitmapCache::parse_color(into_u8(color), rgb);
     // there is no need to scale created solid bitmap
-#ifndef __linux__
+#if !defined(__linux__) && !defined(__NetBSD__)
     return bmp_cache.mksolid(icon_width, icon_height, rgb, true);
 #else
     wxIcon icon;
@@ -210,7 +210,7 @@ void ModelNode::UpdateIcons()
     if (m_icon_name.empty())
         return;
 
-#ifdef __linux__
+#if defined(__linux__) || defined(__NetBSD__)
     m_icon.CopyFromBitmap(create_scaled_bitmap(m_icon_name, m_parent_win, 16, !m_toggle));
 #else
     m_icon = create_scaled_bitmap(m_icon_name, m_parent_win, 16, !m_toggle);
@@ -361,7 +361,7 @@ void DiffModel::GetValue(wxVariant& vari
     case colToggle:
         variant = node->m_toggle;
         break;
-#ifdef __linux__
+#if defined(__linux__) || defined(__NetBSD__)
     case colIconText:
         variant << wxDataViewIconText(node->m_text, node->m_icon);
         break;
@@ -398,7 +398,7 @@ bool DiffModel::SetValue(const wxVariant
     case colToggle:
         node->m_toggle = variant.GetBool();
         return true;
-#ifdef __linux__
+#if defined(__linux__) || defined(__NetBSD__)
     case colIconText: {
         wxDataViewIconText data;
         data << variant;
@@ -603,7 +603,7 @@ DiffViewCtrl::DiffViewCtrl(wxWindow* par
 void DiffViewCtrl::AppendBmpTextColumn(const wxString& label, unsigned model_column, int width, bool set_expander/* = false*/)
 {
     m_columns_width.emplace(this->GetColumnCount(), width);
-#ifdef __linux__
+#if defined(__linux__) || defined(__NetBSD__)
     wxDataViewIconTextRenderer* rd = new wxDataViewIconTextRenderer();
 #ifdef SUPPORTS_MARKUP
     rd->EnableMarkup(true);
