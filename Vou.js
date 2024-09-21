async function saveVoucherCode() {
    // Open a new tab
    const newTab = window.open('', '_blank');
    // Create a div container
    const container = newTab.document.createElement('div');
    container.style.padding = '4px';
    container.style.fontSize = '40px';
    container.style.width = '100%';
    // Create an h1 element
    var h1 = newTab.document.createElement('h1');
    // Set the content of the h1 element
    h1.textContent = 'Bắt đầu lưu mã!';
    // Append the h1 element to the container div
    container.appendChild(h1);
    // Append the container div to the body of the new tab
    newTab.document.body.appendChild(container);

    const API_URL =
        'https://raw.githubusercontent.com/kienqb/kienqb.github.io/refs/heads/main/Voucher';

    // const API_URL =
    //     'http://localhost:8080/api/v1/shopeexu/all_voucher?status=1';
    const allVoucerRes = await fetch(API_URL, {
        method: 'GET',
    });

    const allVoucherData = await allVoucerRes.json();
    const voucherList = allVoucherData.data.allVoucher;
    for (const voucher of voucherList) {
        const raw = JSON.stringify({
            voucher_code: voucher.voucher_code || 'VIDEO-878580758937600',
            voucher_promotionid: voucher.voucher_promotionid || 878580758937600,
            signature:
                voucher.signature ||
                'b0f44b2bfe8426960be3770e80e303e4f1d14f36bfc4aa7a9317ad327a4865cc',
            signature_source: '0',
        });

        const requestOptions = {
            method: 'POST',
            headers: {
                'content-type': 'application/json',
            },
            body: raw,
        };

        try {
            const response = await fetch(
                'https://shopee.vn/api/v2/voucher_wallet/save_voucher',
                requestOptions
            );
            const data = await response.json();
            if (!data.data) continue;
            const { error, error_msg } = data;
            // Create an voucherMessage element
            const voucherMessage = newTab.document.createElement('p');
            // Set the content of the voucherMessage element
            voucherMessage.textContent = `${voucher.voucher_name}: ${
                error ? error_msg : 'Lưu thành công'
            }`;
            // Append the voucherMessage element to the body of the new tab
            container.appendChild(voucherMessage);
        } catch (error) {
            console.log(error);
        }
    }

    // Create an anchor element
    const anchor = newTab.document.createElement('a');
    // Set the href attribute to google.com
    anchor.href = 'https://shope.ee/8UmenBJsPY';

    // Set the inner text of the anchor element
    anchor.textContent = 'Xem Ví Voucher Ngay!';
    // Apply CSS styles to the anchor element
    anchor.style.backgroundColor = '#f97316';
    anchor.style.color = 'white';
    anchor.style.width = '100%';
    anchor.style.padding = '20px';
    anchor.style.textDecoration = 'none';
    anchor.style.borderRadius = '6px';
    anchor.style.height = '60px';
    anchor.style.display = 'block';
    anchor.style.textAlign = 'center';

    container.appendChild(anchor);

    document.location.href = 'https://chietkhau.pro';
}
saveVoucherCode();
